#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct sony_btf_mpx {int mpxmode; int audmode; int /*<<< orphan*/  sd; } ;
struct i2c_msg {int len; int* buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {scalar_t__ audio_mode; int source; int modus; int acb; int fm_prescale; int nicam_prescale; int scart_prescale; int system; int volume; } ;

/* Variables and functions */
#define  AUD_A2 134 
 scalar_t__ AUD_MONO ; 
#define  AUD_NICAM 133 
#define  AUD_NICAM_L 132 
 scalar_t__ I2C_M_RD ; 
#define  V4L2_TUNER_MODE_LANG1 131 
#define  V4L2_TUNER_MODE_LANG2 130 
#define  V4L2_TUNER_MODE_MONO 129 
#define  V4L2_TUNER_MODE_STEREO 128 
 int /*<<< orphan*/  i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 TYPE_1__* mpx_audio_modes ; 
 int /*<<< orphan*/  mpx_write (struct i2c_client*,int,int,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_info (struct i2c_client*,char*,int,int,...) ; 

__attribute__((used)) static int mpx_setup(struct sony_btf_mpx *t)
{
	struct i2c_client *client = v4l2_get_subdevdata(&t->sd);
	u16 source = 0;
	u8 buffer[3];
	struct i2c_msg msg;
	int mode = t->mpxmode;

	/* reset MPX */
	buffer[0] = 0x00;
	buffer[1] = 0x80;
	buffer[2] = 0x00;
	msg.addr = client->addr;
	msg.flags = 0;
	msg.len = 3;
	msg.buf = buffer;
	i2c_transfer(client->adapter, &msg, 1);
	buffer[1] = 0x00;
	i2c_transfer(client->adapter, &msg, 1);

	if (t->audmode != V4L2_TUNER_MODE_MONO)
		mode++;

	if (mpx_audio_modes[mode].audio_mode != AUD_MONO) {
		switch (t->audmode) {
		case V4L2_TUNER_MODE_MONO:
			switch (mpx_audio_modes[mode].audio_mode) {
			case AUD_A2:
				source = mpx_audio_modes[mode].source;
				break;
			case AUD_NICAM:
				source = 0x0000;
				break;
			case AUD_NICAM_L:
				source = 0x0200;
				break;
			default:
				break;
			}
			break;
		case V4L2_TUNER_MODE_STEREO:
			source = mpx_audio_modes[mode].source;
			break;
		case V4L2_TUNER_MODE_LANG1:
			source = 0x0300;
			break;
		case V4L2_TUNER_MODE_LANG2:
			source = 0x0400;
			break;
		}
		source |= mpx_audio_modes[mode].source & 0x00ff;
	} else
		source = mpx_audio_modes[mode].source;

	mpx_write(client, 0x10, 0x0030, mpx_audio_modes[mode].modus);
	mpx_write(client, 0x12, 0x0008, source);
	mpx_write(client, 0x12, 0x0013, mpx_audio_modes[mode].acb);
	mpx_write(client, 0x12, 0x000e,
			mpx_audio_modes[mode].fm_prescale);
	mpx_write(client, 0x12, 0x0010,
			mpx_audio_modes[mode].nicam_prescale);
	mpx_write(client, 0x12, 0x000d,
			mpx_audio_modes[mode].scart_prescale);
	mpx_write(client, 0x10, 0x0020, mpx_audio_modes[mode].system);
	mpx_write(client, 0x12, 0x0000, mpx_audio_modes[mode].volume);
	if (mpx_audio_modes[mode].audio_mode == AUD_A2)
		mpx_write(client, 0x10, 0x0022,
			t->audmode == V4L2_TUNER_MODE_MONO ? 0x07f0 : 0x0190);

#ifdef MPX_DEBUG
	{
		u8 buf1[3], buf2[2];
		struct i2c_msg msgs[2];

		v4l2_info(client,
			"MPX registers: %04x %04x %04x %04x %04x %04x %04x %04x\n",
			mpx_audio_modes[mode].modus,
			source,
			mpx_audio_modes[mode].acb,
			mpx_audio_modes[mode].fm_prescale,
			mpx_audio_modes[mode].nicam_prescale,
			mpx_audio_modes[mode].scart_prescale,
			mpx_audio_modes[mode].system,
			mpx_audio_modes[mode].volume);
		buf1[0] = 0x11;
		buf1[1] = 0x00;
		buf1[2] = 0x7e;
		msgs[0].addr = client->addr;
		msgs[0].flags = 0;
		msgs[0].len = 3;
		msgs[0].buf = buf1;
		msgs[1].addr = client->addr;
		msgs[1].flags = I2C_M_RD;
		msgs[1].len = 2;
		msgs[1].buf = buf2;
		i2c_transfer(client->adapter, msgs, 2);
		v4l2_info(client, "MPX system: %02x%02x\n",
				buf2[0], buf2[1]);
		buf1[0] = 0x11;
		buf1[1] = 0x02;
		buf1[2] = 0x00;
		i2c_transfer(client->adapter, msgs, 2);
		v4l2_info(client, "MPX status: %02x%02x\n",
				buf2[0], buf2[1]);
	}
#endif
	return 0;
}
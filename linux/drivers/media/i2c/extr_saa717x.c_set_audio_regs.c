#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;
struct saa717x_state {int audio_input; int audio_main_volume; long audio_main_vol_l; long audio_main_vol_r; int audio_main_bass; int audio_main_treble; scalar_t__ audio_main_mute; scalar_t__ audio_main_balance; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug ; 
 int min (scalar_t__,int) ; 
 int /*<<< orphan*/  saa717x_write (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static int set_audio_regs(struct v4l2_subdev *sd,
		struct saa717x_state *decoder)
{
	u8 mute = 0xac; /* -84 dB */
	u32 val;
	unsigned int work_l, work_r;

	/* set SIF analog I/O select */
	saa717x_write(sd, 0x0594, decoder->audio_input);
	v4l2_dbg(1, debug, sd, "set audio input %d\n",
			decoder->audio_input);

	/* normalize ( 65535 to 0 -> 24 to -40 (not -84)) */
	work_l = (min(65536 - decoder->audio_main_balance, 32768) * decoder->audio_main_volume) / 32768;
	work_r = (min(decoder->audio_main_balance, (u16)32768) * decoder->audio_main_volume) / 32768;
	decoder->audio_main_vol_l = (long)work_l * (24 - (-40)) / 65535 - 40;
	decoder->audio_main_vol_r = (long)work_r * (24 - (-40)) / 65535 - 40;

	/* set main volume */
	/* main volume L[7-0],R[7-0],0x00  24=24dB,-83dB, -84(mute) */
	/*    def:0dB->6dB(MPG600GR) */
	/* if mute is on, set mute */
	if (decoder->audio_main_mute) {
		val = mute | (mute << 8);
	} else {
		val = (u8)decoder->audio_main_vol_l |
			((u8)decoder->audio_main_vol_r << 8);
	}

	saa717x_write(sd, 0x480, val);

	/* set bass and treble */
	val = decoder->audio_main_bass & 0x1f;
	val |= (decoder->audio_main_treble & 0x1f) << 5;
	saa717x_write(sd, 0x488, val);
	return 0;
}
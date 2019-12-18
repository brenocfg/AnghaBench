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
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_sliced_vbi_format {int** service_lines; int service_set; } ;
struct i2c_client {int dummy; } ;
struct cx25840_state {int std; int vbi_regs_offset; } ;

/* Variables and functions */
#define  V4L2_SLICED_CAPTION_525 131 
#define  V4L2_SLICED_TELETEXT_B 130 
#define  V4L2_SLICED_VPS 129 
#define  V4L2_SLICED_WSS_625 128 
 int V4L2_STD_525_60 ; 
 int cx25840_read (struct i2c_client*,int) ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 
 struct cx25840_state* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

int cx25840_g_sliced_fmt(struct v4l2_subdev *sd, struct v4l2_sliced_vbi_format *svbi)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct cx25840_state *state = to_state(sd);
	static const u16 lcr2vbi[] = {
		0, V4L2_SLICED_TELETEXT_B, 0,	/* 1 */
		0, V4L2_SLICED_WSS_625, 0,	/* 4 */
		V4L2_SLICED_CAPTION_525,	/* 6 */
		0, 0, V4L2_SLICED_VPS, 0, 0,	/* 9 */
		0, 0, 0, 0
	};
	int is_pal = !(state->std & V4L2_STD_525_60);
	int i;

	memset(svbi->service_lines, 0, sizeof(svbi->service_lines));
	svbi->service_set = 0;
	/* we're done if raw VBI is active */
	/* TODO: this will have to be changed for generic_mode VBI */
	if ((cx25840_read(client, 0x404) & 0x10) == 0)
		return 0;

	if (is_pal) {
		for (i = 7; i <= 23; i++) {
			u8 v = cx25840_read(client,
				 state->vbi_regs_offset + 0x424 + i - 7);

			svbi->service_lines[0][i] = lcr2vbi[v >> 4];
			svbi->service_lines[1][i] = lcr2vbi[v & 0xf];
			svbi->service_set |= svbi->service_lines[0][i] |
					     svbi->service_lines[1][i];
		}
	} else {
		for (i = 10; i <= 21; i++) {
			u8 v = cx25840_read(client,
				state->vbi_regs_offset + 0x424 + i - 10);

			svbi->service_lines[0][i] = lcr2vbi[v >> 4];
			svbi->service_lines[1][i] = lcr2vbi[v & 0xf];
			svbi->service_set |= svbi->service_lines[0][i] |
					     svbi->service_lines[1][i];
		}
	}
	return 0;
}
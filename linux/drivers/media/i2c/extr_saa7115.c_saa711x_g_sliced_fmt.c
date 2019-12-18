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
typedef  void* u16 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_sliced_vbi_format {int** service_lines; int service_set; } ;

/* Variables and functions */
 scalar_t__ R_41_LCR_BASE ; 
 scalar_t__ R_80_GLOBAL_CNTL_1 ; 
#define  V4L2_SLICED_CAPTION_525 131 
#define  V4L2_SLICED_TELETEXT_B 130 
#define  V4L2_SLICED_VPS 129 
#define  V4L2_SLICED_WSS_625 128 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 
 int saa711x_read (struct v4l2_subdev*,scalar_t__) ; 

__attribute__((used)) static int saa711x_g_sliced_fmt(struct v4l2_subdev *sd, struct v4l2_sliced_vbi_format *sliced)
{
	static u16 lcr2vbi[] = {
		0, V4L2_SLICED_TELETEXT_B, 0,	/* 1 */
		0, V4L2_SLICED_CAPTION_525,	/* 4 */
		V4L2_SLICED_WSS_625, 0,		/* 5 */
		V4L2_SLICED_VPS, 0, 0, 0, 0,	/* 7 */
		0, 0, 0, 0
	};
	int i;

	memset(sliced->service_lines, 0, sizeof(sliced->service_lines));
	sliced->service_set = 0;
	/* done if using raw VBI */
	if (saa711x_read(sd, R_80_GLOBAL_CNTL_1) & 0x10)
		return 0;
	for (i = 2; i <= 23; i++) {
		u8 v = saa711x_read(sd, i - 2 + R_41_LCR_BASE);

		sliced->service_lines[0][i] = lcr2vbi[v >> 4];
		sliced->service_lines[1][i] = lcr2vbi[v & 0xf];
		sliced->service_set |=
			sliced->service_lines[0][i] | sliced->service_lines[1][i];
	}
	return 0;
}
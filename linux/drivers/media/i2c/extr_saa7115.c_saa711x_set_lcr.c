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
struct v4l2_subdev {int dummy; } ;
struct v4l2_sliced_vbi_format {int** service_lines; } ;
struct saa711x_state {int std; scalar_t__ ident; } ;

/* Variables and functions */
 scalar_t__ R_41_LCR_BASE ; 
 scalar_t__ SAA7115 ; 
#define  V4L2_SLICED_CAPTION_525 131 
#define  V4L2_SLICED_TELETEXT_B 130 
#define  V4L2_SLICED_VPS 129 
#define  V4L2_SLICED_WSS_625 128 
 int V4L2_STD_625_50 ; 
 int /*<<< orphan*/  saa7115_cfg_vbi_off ; 
 int /*<<< orphan*/  saa7115_cfg_vbi_on ; 
 int /*<<< orphan*/  saa711x_has_reg (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  saa711x_write (struct v4l2_subdev*,scalar_t__,int) ; 
 int /*<<< orphan*/  saa711x_writeregs (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 struct saa711x_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static void saa711x_set_lcr(struct v4l2_subdev *sd, struct v4l2_sliced_vbi_format *fmt)
{
	struct saa711x_state *state = to_state(sd);
	int is_50hz = (state->std & V4L2_STD_625_50);
	u8 lcr[24];
	int i, x;

#if 1
	/* saa7113/7114/7118 VBI support are experimental */
	if (!saa711x_has_reg(state->ident, R_41_LCR_BASE))
		return;

#else
	/* SAA7113 and SAA7118 also should support VBI - Need testing */
	if (state->ident != SAA7115)
		return;
#endif

	for (i = 0; i <= 23; i++)
		lcr[i] = 0xff;

	if (fmt == NULL) {
		/* raw VBI */
		if (is_50hz)
			for (i = 6; i <= 23; i++)
				lcr[i] = 0xdd;
		else
			for (i = 10; i <= 21; i++)
				lcr[i] = 0xdd;
	} else {
		/* sliced VBI */
		/* first clear lines that cannot be captured */
		if (is_50hz) {
			for (i = 0; i <= 5; i++)
				fmt->service_lines[0][i] =
					fmt->service_lines[1][i] = 0;
		}
		else {
			for (i = 0; i <= 9; i++)
				fmt->service_lines[0][i] =
					fmt->service_lines[1][i] = 0;
			for (i = 22; i <= 23; i++)
				fmt->service_lines[0][i] =
					fmt->service_lines[1][i] = 0;
		}

		/* Now set the lcr values according to the specified service */
		for (i = 6; i <= 23; i++) {
			lcr[i] = 0;
			for (x = 0; x <= 1; x++) {
				switch (fmt->service_lines[1-x][i]) {
					case 0:
						lcr[i] |= 0xf << (4 * x);
						break;
					case V4L2_SLICED_TELETEXT_B:
						lcr[i] |= 1 << (4 * x);
						break;
					case V4L2_SLICED_CAPTION_525:
						lcr[i] |= 4 << (4 * x);
						break;
					case V4L2_SLICED_WSS_625:
						lcr[i] |= 5 << (4 * x);
						break;
					case V4L2_SLICED_VPS:
						lcr[i] |= 7 << (4 * x);
						break;
				}
			}
		}
	}

	/* write the lcr registers */
	for (i = 2; i <= 23; i++) {
		saa711x_write(sd, i - 2 + R_41_LCR_BASE, lcr[i]);
	}

	/* enable/disable raw VBI capturing */
	saa711x_writeregs(sd, fmt == NULL ?
				saa7115_cfg_vbi_on :
				saa7115_cfg_vbi_off);
}
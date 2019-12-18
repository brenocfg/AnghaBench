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
typedef  int v4l2_std_id ;
struct v4l2_subdev {int dummy; } ;
struct saa711x_state {scalar_t__ ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_1E_STATUS_BYTE_1_VD_DEC ; 
 int /*<<< orphan*/  R_1F_STATUS_BYTE_2_VD_DEC ; 
 scalar_t__ SAA7115 ; 
 int V4L2_STD_525_60 ; 
 int V4L2_STD_625_50 ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_PAL ; 
 int V4L2_STD_PAL_60 ; 
 int V4L2_STD_PAL_M ; 
 int V4L2_STD_PAL_N ; 
 int V4L2_STD_PAL_Nc ; 
 int V4L2_STD_SECAM ; 
 int V4L2_STD_UNKNOWN ; 
 int /*<<< orphan*/  debug ; 
 int saa711x_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 struct saa711x_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static int saa711x_querystd(struct v4l2_subdev *sd, v4l2_std_id *std)
{
	struct saa711x_state *state = to_state(sd);
	int reg1f, reg1e;

	/*
	 * The V4L2 core already initializes std with all supported
	 * Standards. All driver needs to do is to mask it, to remove
	 * standards that don't apply from the mask
	 */

	reg1f = saa711x_read(sd, R_1F_STATUS_BYTE_2_VD_DEC);

	if (state->ident == SAA7115) {
		reg1e = saa711x_read(sd, R_1E_STATUS_BYTE_1_VD_DEC);

		v4l2_dbg(1, debug, sd, "Status byte 1 (0x1e)=0x%02x\n", reg1e);

		switch (reg1e & 0x03) {
		case 1:
			*std &= V4L2_STD_NTSC;
			break;
		case 2:
			/*
			 * V4L2_STD_PAL just cover the european PAL standards.
			 * This is wrong, as the device could also be using an
			 * other PAL standard.
			 */
			*std &= V4L2_STD_PAL   | V4L2_STD_PAL_N  | V4L2_STD_PAL_Nc |
				V4L2_STD_PAL_M | V4L2_STD_PAL_60;
			break;
		case 3:
			*std &= V4L2_STD_SECAM;
			break;
		default:
			*std = V4L2_STD_UNKNOWN;
			/* Can't detect anything */
			break;
		}
	}

	v4l2_dbg(1, debug, sd, "Status byte 2 (0x1f)=0x%02x\n", reg1f);

	/* horizontal/vertical not locked */
	if (reg1f & 0x40) {
		*std = V4L2_STD_UNKNOWN;
		goto ret;
	}

	if (reg1f & 0x20)
		*std &= V4L2_STD_525_60;
	else
		*std &= V4L2_STD_625_50;

ret:
	v4l2_dbg(1, debug, sd, "detected std mask = %08Lx\n", *std);

	return 0;
}
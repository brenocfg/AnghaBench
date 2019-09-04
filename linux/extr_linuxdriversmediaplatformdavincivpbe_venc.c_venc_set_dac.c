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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VDAC_COMPONENT ; 
 int /*<<< orphan*/  VDAC_S_VIDEO ; 
 int /*<<< orphan*/  VENC_DACSEL ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int /*<<< orphan*/ ,int,struct v4l2_subdev*,char*) ; 
 int /*<<< orphan*/  venc_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int venc_set_dac(struct v4l2_subdev *sd, u32 out_index)
{
	switch (out_index) {
	case 0:
		v4l2_dbg(debug, 1, sd, "Setting output to Composite\n");
		venc_write(sd, VENC_DACSEL, 0);
		break;
	case 1:
		v4l2_dbg(debug, 1, sd, "Setting output to Component\n");
		venc_write(sd, VENC_DACSEL, VDAC_COMPONENT);
		break;
	case 2:
		v4l2_dbg(debug, 1, sd, "Setting output to S-video\n");
		venc_write(sd, VENC_DACSEL, VDAC_S_VIDEO);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
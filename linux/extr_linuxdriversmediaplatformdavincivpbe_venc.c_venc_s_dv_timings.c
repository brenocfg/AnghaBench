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
typedef  int u32 ;
struct venc_state {scalar_t__ venc_type; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int height; } ;
struct v4l2_dv_timings {TYPE_1__ bt; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VDAC_CONFIG_HD_V2 ; 
 scalar_t__ VPBE_VERSION_2 ; 
 int /*<<< orphan*/  debug ; 
 struct venc_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int /*<<< orphan*/ ,int,struct v4l2_subdev*,char*) ; 
 int /*<<< orphan*/  vdaccfg_write (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int venc_set_1080i30_internal (struct v4l2_subdev*) ; 
 int venc_set_480p59_94 (struct v4l2_subdev*) ; 
 int venc_set_576p50 (struct v4l2_subdev*) ; 
 int venc_set_720p60_internal (struct v4l2_subdev*) ; 

__attribute__((used)) static int venc_s_dv_timings(struct v4l2_subdev *sd,
			    struct v4l2_dv_timings *dv_timings)
{
	struct venc_state *venc = to_state(sd);
	u32 height = dv_timings->bt.height;
	int ret;

	v4l2_dbg(debug, 1, sd, "venc_s_dv_timings\n");

	if (height == 576)
		return venc_set_576p50(sd);
	else if (height == 480)
		return venc_set_480p59_94(sd);
	else if ((height == 720) &&
			(venc->venc_type == VPBE_VERSION_2)) {
		/* TBD setup internal 720p mode here */
		ret = venc_set_720p60_internal(sd);
		/* for DM365 VPBE, there is DAC inside */
		vdaccfg_write(sd, VDAC_CONFIG_HD_V2);
		return ret;
	} else if ((height == 1080) &&
		(venc->venc_type == VPBE_VERSION_2)) {
		/* TBD setup internal 1080i mode here */
		ret = venc_set_1080i30_internal(sd);
		/* for DM365 VPBE, there is DAC inside */
		vdaccfg_write(sd, VDAC_CONFIG_HD_V2);
		return ret;
	}
	return -EINVAL;
}
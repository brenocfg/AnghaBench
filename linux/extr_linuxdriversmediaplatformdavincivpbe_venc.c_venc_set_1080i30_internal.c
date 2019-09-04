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
struct venc_state {int /*<<< orphan*/  venc_type; struct venc_platform_data* pdata; } ;
struct venc_platform_data {scalar_t__ (* setup_clock ) (int /*<<< orphan*/ ,int) ;} ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int HDTV_1080I ; 
 int /*<<< orphan*/  VENC_OSDCLK0 ; 
 int /*<<< orphan*/  VENC_OSDCLK1 ; 
 int /*<<< orphan*/  VENC_VMOD ; 
 int VENC_VMOD_HDMD ; 
 int VENC_VMOD_TVTYP ; 
 int VENC_VMOD_TVTYP_SHIFT ; 
 int VENC_VMOD_VENC ; 
 int VENC_VMOD_VIE ; 
 int VENC_VMOD_VIE_SHIFT ; 
 int /*<<< orphan*/  VENC_XHINTVL ; 
 int /*<<< orphan*/  VPBE_ENC_DV_TIMINGS ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int) ; 
 struct venc_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  venc_enable_vpss_clock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  venc_enabledigitaloutput (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  venc_modify (struct v4l2_subdev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  venc_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int venc_set_1080i30_internal(struct v4l2_subdev *sd)
{
	struct venc_state *venc = to_state(sd);
	struct venc_platform_data *pdata = venc->pdata;

	if (pdata->setup_clock(VPBE_ENC_DV_TIMINGS, 74250000) < 0)
		return -EINVAL;

	venc_enable_vpss_clock(venc->venc_type, VPBE_ENC_DV_TIMINGS, 74250000);
	venc_enabledigitaloutput(sd, 0);

	venc_write(sd, VENC_OSDCLK0, 0);
	venc_write(sd, VENC_OSDCLK1, 1);


	venc_write(sd, VENC_VMOD, 0);
	/* DM365 component HD mode */
	venc_modify(sd, VENC_VMOD, (1 << VENC_VMOD_VIE_SHIFT),
		    VENC_VMOD_VIE);
	venc_modify(sd, VENC_VMOD, VENC_VMOD_HDMD, VENC_VMOD_HDMD);
	venc_modify(sd, VENC_VMOD, (HDTV_1080I << VENC_VMOD_TVTYP_SHIFT),
		    VENC_VMOD_TVTYP);
	venc_modify(sd, VENC_VMOD, VENC_VMOD_VENC, VENC_VMOD_VENC);
	venc_write(sd, VENC_XHINTVL, 0);
	return 0;
}
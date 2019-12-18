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
struct venc_state {scalar_t__ venc_type; struct venc_platform_data* pdata; } ;
struct venc_platform_data {scalar_t__ (* setup_clock ) (int /*<<< orphan*/ ,int) ;} ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int HDTV_625P ; 
 int /*<<< orphan*/  VDAC_CONFIG_HD_V2 ; 
 int /*<<< orphan*/  VENC_OSDCLK0 ; 
 int /*<<< orphan*/  VENC_OSDCLK1 ; 
 int /*<<< orphan*/  VENC_VDPRO ; 
 int VENC_VDPRO_DAFRQ ; 
 int VENC_VDPRO_DAUPS ; 
 int /*<<< orphan*/  VENC_VMOD ; 
 int VENC_VMOD_HDMD ; 
 int VENC_VMOD_TVTYP ; 
 int VENC_VMOD_TVTYP_SHIFT ; 
 int VENC_VMOD_VDMD ; 
 int VENC_VMOD_VDMD_SHIFT ; 
 int VENC_VMOD_VDMD_YCBCR8 ; 
 int VENC_VMOD_VENC ; 
 int VENC_VMOD_VIE ; 
 int VENC_VMOD_VIE_SHIFT ; 
 int /*<<< orphan*/  VPBE_ENC_DV_TIMINGS ; 
 scalar_t__ VPBE_VERSION_1 ; 
 scalar_t__ VPBE_VERSION_2 ; 
 int /*<<< orphan*/  debug ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int) ; 
 struct venc_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int /*<<< orphan*/ ,int,struct v4l2_subdev*,char*) ; 
 int /*<<< orphan*/  vdaccfg_write (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  venc_enable_vpss_clock (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  venc_enabledigitaloutput (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  venc_modify (struct v4l2_subdev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  venc_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int venc_set_576p50(struct v4l2_subdev *sd)
{
	struct venc_state *venc = to_state(sd);
	struct venc_platform_data *pdata = venc->pdata;

	v4l2_dbg(debug, 2, sd, "venc_set_576p50\n");

	if (venc->venc_type != VPBE_VERSION_1 &&
	    venc->venc_type != VPBE_VERSION_2)
		return -EINVAL;
	/* Setup clock at VPSS & VENC for SD */
	if (pdata->setup_clock(VPBE_ENC_DV_TIMINGS, 27000000) < 0)
		return -EINVAL;

	venc_enable_vpss_clock(venc->venc_type, VPBE_ENC_DV_TIMINGS, 27000000);
	venc_enabledigitaloutput(sd, 0);

	if (venc->venc_type == VPBE_VERSION_2)
		vdaccfg_write(sd, VDAC_CONFIG_HD_V2);

	venc_write(sd, VENC_OSDCLK0, 0);
	venc_write(sd, VENC_OSDCLK1, 1);

	if (venc->venc_type == VPBE_VERSION_1) {
		venc_modify(sd, VENC_VDPRO, VENC_VDPRO_DAFRQ,
			    VENC_VDPRO_DAFRQ);
		venc_modify(sd, VENC_VDPRO, VENC_VDPRO_DAUPS,
			    VENC_VDPRO_DAUPS);
	}

	venc_write(sd, VENC_VMOD, 0);
	venc_modify(sd, VENC_VMOD, (1 << VENC_VMOD_VIE_SHIFT),
		    VENC_VMOD_VIE);
	venc_modify(sd, VENC_VMOD, VENC_VMOD_HDMD, VENC_VMOD_HDMD);
	venc_modify(sd, VENC_VMOD, (HDTV_625P << VENC_VMOD_TVTYP_SHIFT),
		    VENC_VMOD_TVTYP);

	venc_modify(sd, VENC_VMOD, VENC_VMOD_VDMD_YCBCR8 <<
		    VENC_VMOD_VDMD_SHIFT, VENC_VMOD_VDMD);
	venc_modify(sd, VENC_VMOD, VENC_VMOD_VENC, VENC_VMOD_VENC);

	return 0;
}
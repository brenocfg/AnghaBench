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
struct venc_platform_data {scalar_t__ (* setup_clock ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_STD_525_60 ; 
 int /*<<< orphan*/  VDAC_CONFIG_SD_V2 ; 
 int /*<<< orphan*/  VDAC_CONFIG_SD_V3 ; 
 int /*<<< orphan*/  VENC_CLKCTL ; 
 int /*<<< orphan*/  VENC_DACTST ; 
 int /*<<< orphan*/  VENC_VDPRO ; 
 int VENC_VDPRO_DAFRQ ; 
 int VENC_VDPRO_DAUPS ; 
 int /*<<< orphan*/  VENC_VIDCTL ; 
 int /*<<< orphan*/  VENC_VMOD ; 
 int VENC_VMOD_TVTYP ; 
 int VENC_VMOD_TVTYP_SHIFT ; 
 int VENC_VMOD_VENC ; 
 int VENC_VMOD_VIE ; 
 int VENC_VMOD_VIE_SHIFT ; 
 int VENC_VMOD_VMD ; 
 int /*<<< orphan*/  VENC_YCCCTL ; 
 int /*<<< orphan*/  VPBE_ENC_STD ; 
 scalar_t__ VPBE_VERSION_2 ; 
 scalar_t__ VPBE_VERSION_3 ; 
 int /*<<< orphan*/  VPSS_VENC_CLOCK_SEL ; 
 int /*<<< orphan*/  debug ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct venc_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int /*<<< orphan*/ ,int,struct v4l2_subdev*,char*) ; 
 int /*<<< orphan*/  vdaccfg_write (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  venc_enable_vpss_clock (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  venc_enabledigitaloutput (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  venc_modify (struct v4l2_subdev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  venc_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vpss_enable_clock (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int venc_set_ntsc(struct v4l2_subdev *sd)
{
	struct venc_state *venc = to_state(sd);
	struct venc_platform_data *pdata = venc->pdata;

	v4l2_dbg(debug, 2, sd, "venc_set_ntsc\n");

	/* Setup clock at VPSS & VENC for SD */
	vpss_enable_clock(VPSS_VENC_CLOCK_SEL, 1);
	if (pdata->setup_clock(VPBE_ENC_STD, V4L2_STD_525_60) < 0)
		return -EINVAL;

	venc_enable_vpss_clock(venc->venc_type, VPBE_ENC_STD, V4L2_STD_525_60);
	venc_enabledigitaloutput(sd, 0);

	if (venc->venc_type == VPBE_VERSION_3) {
		venc_write(sd, VENC_CLKCTL, 0x01);
		venc_write(sd, VENC_VIDCTL, 0);
		vdaccfg_write(sd, VDAC_CONFIG_SD_V3);
	} else if (venc->venc_type == VPBE_VERSION_2) {
		venc_write(sd, VENC_CLKCTL, 0x01);
		venc_write(sd, VENC_VIDCTL, 0);
		vdaccfg_write(sd, VDAC_CONFIG_SD_V2);
	} else {
		/* to set VENC CLK DIV to 1 - final clock is 54 MHz */
		venc_modify(sd, VENC_VIDCTL, 0, 1 << 1);
		/* Set REC656 Mode */
		venc_write(sd, VENC_YCCCTL, 0x1);
		venc_modify(sd, VENC_VDPRO, 0, VENC_VDPRO_DAFRQ);
		venc_modify(sd, VENC_VDPRO, 0, VENC_VDPRO_DAUPS);
	}

	venc_write(sd, VENC_VMOD, 0);
	venc_modify(sd, VENC_VMOD, (1 << VENC_VMOD_VIE_SHIFT),
			VENC_VMOD_VIE);
	venc_modify(sd, VENC_VMOD, (0 << VENC_VMOD_VMD), VENC_VMOD_VMD);
	venc_modify(sd, VENC_VMOD, (0 << VENC_VMOD_TVTYP_SHIFT),
			VENC_VMOD_TVTYP);
	venc_write(sd, VENC_DACTST, 0x0);
	venc_modify(sd, VENC_VMOD, VENC_VMOD_VENC, VENC_VMOD_VENC);

	return 0;
}
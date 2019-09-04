#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct msm_kms {TYPE_2__* funcs; } ;
struct msm_edp {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  encoder; } ;
struct msm_drm_private {struct msm_kms* kms; } ;
struct edp_connector {struct msm_edp* edp; } ;
struct drm_display_mode {int clock; } ;
struct TYPE_6__ {int bpc; } ;
struct drm_connector {TYPE_3__ display_info; TYPE_1__* dev; } ;
struct TYPE_5__ {long (* round_pixclk ) (struct msm_kms*,long,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,long,long) ; 
 int MODE_BAD ; 
 int MODE_CLOCK_RANGE ; 
 int MODE_OK ; 
 int /*<<< orphan*/  msm_edp_ctrl_pixel_clock_valid (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 long stub1 (struct msm_kms*,long,int /*<<< orphan*/ ) ; 
 struct edp_connector* to_edp_connector (struct drm_connector*) ; 

__attribute__((used)) static int edp_connector_mode_valid(struct drm_connector *connector,
				 struct drm_display_mode *mode)
{
	struct edp_connector *edp_connector = to_edp_connector(connector);
	struct msm_edp *edp = edp_connector->edp;
	struct msm_drm_private *priv = connector->dev->dev_private;
	struct msm_kms *kms = priv->kms;
	long actual, requested;

	requested = 1000 * mode->clock;
	actual = kms->funcs->round_pixclk(kms,
			requested, edp_connector->edp->encoder);

	DBG("requested=%ld, actual=%ld", requested, actual);
	if (actual != requested)
		return MODE_CLOCK_RANGE;

	if (!msm_edp_ctrl_pixel_clock_valid(
		edp->ctrl, mode->clock, NULL, NULL))
		return MODE_CLOCK_RANGE;

	/* Invalidate all modes if color format is not supported */
	if (connector->display_info.bpc > 8)
		return MODE_BAD;

	return MODE_OK;
}
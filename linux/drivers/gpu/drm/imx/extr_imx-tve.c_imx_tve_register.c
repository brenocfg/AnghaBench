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
struct imx_tve {scalar_t__ mode; int /*<<< orphan*/  encoder; int /*<<< orphan*/  connector; int /*<<< orphan*/  ddc; TYPE_1__* dev; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VGA ; 
 int DRM_MODE_ENCODER_DAC ; 
 int DRM_MODE_ENCODER_TVDAC ; 
 scalar_t__ TVE_MODE_VGA ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init_with_ddc (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int imx_drm_encoder_parse_of (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_tve_connector_funcs ; 
 int /*<<< orphan*/  imx_tve_connector_helper_funcs ; 
 int /*<<< orphan*/  imx_tve_encoder_funcs ; 
 int /*<<< orphan*/  imx_tve_encoder_helper_funcs ; 

__attribute__((used)) static int imx_tve_register(struct drm_device *drm, struct imx_tve *tve)
{
	int encoder_type;
	int ret;

	encoder_type = tve->mode == TVE_MODE_VGA ?
				DRM_MODE_ENCODER_DAC : DRM_MODE_ENCODER_TVDAC;

	ret = imx_drm_encoder_parse_of(drm, &tve->encoder, tve->dev->of_node);
	if (ret)
		return ret;

	drm_encoder_helper_add(&tve->encoder, &imx_tve_encoder_helper_funcs);
	drm_encoder_init(drm, &tve->encoder, &imx_tve_encoder_funcs,
			 encoder_type, NULL);

	drm_connector_helper_add(&tve->connector,
			&imx_tve_connector_helper_funcs);
	drm_connector_init_with_ddc(drm, &tve->connector,
				    &imx_tve_connector_funcs,
				    DRM_MODE_CONNECTOR_VGA,
				    tve->ddc);

	drm_connector_attach_encoder(&tve->connector, &tve->encoder);

	return 0;
}
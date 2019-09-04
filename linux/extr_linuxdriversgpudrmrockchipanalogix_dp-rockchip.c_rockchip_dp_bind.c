#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* funcs; } ;
struct TYPE_8__ {int /*<<< orphan*/  get_modes; int /*<<< orphan*/  power_off; int /*<<< orphan*/  power_on_end; int /*<<< orphan*/  power_on_start; int /*<<< orphan*/  dev_type; TYPE_2__* encoder; } ;
struct rockchip_dp_device {TYPE_2__ encoder; int /*<<< orphan*/  adp; TYPE_5__ plat_data; struct drm_device* drm_dev; struct rockchip_dp_chip_data const* data; } ;
struct rockchip_dp_chip_data {int /*<<< orphan*/  chip_type; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* destroy ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  analogix_dp_bind (struct device*,struct drm_device*,TYPE_5__*) ; 
 int /*<<< orphan*/  analogix_dp_psr_set ; 
 struct rockchip_dp_device* dev_get_drvdata (struct device*) ; 
 struct rockchip_dp_chip_data* of_device_get_match_data (struct device*) ; 
 int rockchip_dp_drm_create_encoder (struct rockchip_dp_device*) ; 
 int /*<<< orphan*/  rockchip_dp_get_modes ; 
 int /*<<< orphan*/  rockchip_dp_powerdown ; 
 int /*<<< orphan*/  rockchip_dp_poweron_end ; 
 int /*<<< orphan*/  rockchip_dp_poweron_start ; 
 int rockchip_drm_psr_register (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rockchip_drm_psr_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static int rockchip_dp_bind(struct device *dev, struct device *master,
			    void *data)
{
	struct rockchip_dp_device *dp = dev_get_drvdata(dev);
	const struct rockchip_dp_chip_data *dp_data;
	struct drm_device *drm_dev = data;
	int ret;

	dp_data = of_device_get_match_data(dev);
	if (!dp_data)
		return -ENODEV;

	dp->data = dp_data;
	dp->drm_dev = drm_dev;

	ret = rockchip_dp_drm_create_encoder(dp);
	if (ret) {
		DRM_ERROR("failed to create drm encoder\n");
		return ret;
	}

	dp->plat_data.encoder = &dp->encoder;

	dp->plat_data.dev_type = dp->data->chip_type;
	dp->plat_data.power_on_start = rockchip_dp_poweron_start;
	dp->plat_data.power_on_end = rockchip_dp_poweron_end;
	dp->plat_data.power_off = rockchip_dp_powerdown;
	dp->plat_data.get_modes = rockchip_dp_get_modes;

	ret = rockchip_drm_psr_register(&dp->encoder, analogix_dp_psr_set);
	if (ret < 0)
		goto err_cleanup_encoder;

	dp->adp = analogix_dp_bind(dev, dp->drm_dev, &dp->plat_data);
	if (IS_ERR(dp->adp)) {
		ret = PTR_ERR(dp->adp);
		goto err_unreg_psr;
	}

	return 0;
err_unreg_psr:
	rockchip_drm_psr_unregister(&dp->encoder);
err_cleanup_encoder:
	dp->encoder.funcs->destroy(&dp->encoder);
	return ret;
}
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
typedef  int /*<<< orphan*/  u8 ;
struct msm_dsi {struct drm_encoder* encoder; TYPE_1__* dev; } ;
struct drm_bridge {int /*<<< orphan*/ * funcs; } ;
struct dsi_bridge {struct drm_bridge base; int /*<<< orphan*/  id; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct drm_bridge* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dsi_bridge* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int drm_bridge_attach (struct drm_encoder*,struct drm_bridge*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsi_mgr_bridge_funcs ; 
 struct msm_dsi* dsi_mgr_get_dsi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_dsi_manager_bridge_destroy (struct drm_bridge*) ; 

struct drm_bridge *msm_dsi_manager_bridge_init(u8 id)
{
	struct msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	struct drm_bridge *bridge = NULL;
	struct dsi_bridge *dsi_bridge;
	struct drm_encoder *encoder;
	int ret;

	dsi_bridge = devm_kzalloc(msm_dsi->dev->dev,
				sizeof(*dsi_bridge), GFP_KERNEL);
	if (!dsi_bridge) {
		ret = -ENOMEM;
		goto fail;
	}

	dsi_bridge->id = id;

	encoder = msm_dsi->encoder;

	bridge = &dsi_bridge->base;
	bridge->funcs = &dsi_mgr_bridge_funcs;

	ret = drm_bridge_attach(encoder, bridge, NULL);
	if (ret)
		goto fail;

	return bridge;

fail:
	if (bridge)
		msm_dsi_manager_bridge_destroy(bridge);

	return ERR_PTR(ret);
}
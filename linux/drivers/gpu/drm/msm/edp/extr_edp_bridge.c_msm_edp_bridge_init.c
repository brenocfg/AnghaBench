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
struct msm_edp {int /*<<< orphan*/  encoder; TYPE_1__* dev; } ;
struct drm_bridge {int /*<<< orphan*/ * funcs; } ;
struct edp_bridge {struct drm_bridge base; struct msm_edp* edp; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct drm_bridge* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct edp_bridge* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int drm_bridge_attach (int /*<<< orphan*/ ,struct drm_bridge*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edp_bridge_destroy (struct drm_bridge*) ; 
 int /*<<< orphan*/  edp_bridge_funcs ; 

struct drm_bridge *msm_edp_bridge_init(struct msm_edp *edp)
{
	struct drm_bridge *bridge = NULL;
	struct edp_bridge *edp_bridge;
	int ret;

	edp_bridge = devm_kzalloc(edp->dev->dev,
			sizeof(*edp_bridge), GFP_KERNEL);
	if (!edp_bridge) {
		ret = -ENOMEM;
		goto fail;
	}

	edp_bridge->edp = edp;

	bridge = &edp_bridge->base;
	bridge->funcs = &edp_bridge_funcs;

	ret = drm_bridge_attach(edp->encoder, bridge, NULL);
	if (ret)
		goto fail;

	return bridge;

fail:
	if (bridge)
		edp_bridge_destroy(bridge);

	return ERR_PTR(ret);
}
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
struct msm_edp {int /*<<< orphan*/  ctrl; } ;
struct edp_bridge {struct msm_edp* edp; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  msm_edp_ctrl_power (int /*<<< orphan*/ ,int) ; 
 struct edp_bridge* to_edp_bridge (struct drm_bridge*) ; 

__attribute__((used)) static void edp_bridge_pre_enable(struct drm_bridge *bridge)
{
	struct edp_bridge *edp_bridge = to_edp_bridge(bridge);
	struct msm_edp *edp = edp_bridge->edp;

	DBG("");
	msm_edp_ctrl_power(edp->ctrl, true);
}
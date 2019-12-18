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
struct msm_dsi_manager {int master_dsi_link_id; void* is_sync_needed; void* is_dual_dsi; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct msm_dsi_manager msm_dsim_glb ; 
 void* of_property_read_bool (struct device_node*,char*) ; 

__attribute__((used)) static int dsi_mgr_parse_dual_dsi(struct device_node *np, int id)
{
	struct msm_dsi_manager *msm_dsim = &msm_dsim_glb;

	/* We assume 2 dsi nodes have the same information of dual-dsi and
	 * sync-mode, and only one node specifies master in case of dual mode.
	 */
	if (!msm_dsim->is_dual_dsi)
		msm_dsim->is_dual_dsi = of_property_read_bool(
						np, "qcom,dual-dsi-mode");

	if (msm_dsim->is_dual_dsi) {
		if (of_property_read_bool(np, "qcom,master-dsi"))
			msm_dsim->master_dsi_link_id = id;
		if (!msm_dsim->is_sync_needed)
			msm_dsim->is_sync_needed = of_property_read_bool(
					np, "qcom,sync-dual-dsi");
	}

	return 0;
}
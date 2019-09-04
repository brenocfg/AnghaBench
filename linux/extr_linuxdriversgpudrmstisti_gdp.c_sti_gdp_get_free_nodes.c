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
struct sti_gdp_node_list {int btm_field_paddr; int top_field_paddr; } ;
struct sti_gdp {struct sti_gdp_node_list* node_list; int /*<<< orphan*/  plane; scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ GAM_GDP_NVN_OFFSET ; 
 unsigned int GDP_NODE_NB_BANK ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  sti_plane_to_str (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sti_gdp_node_list *sti_gdp_get_free_nodes(struct sti_gdp *gdp)
{
	int hw_nvn;
	unsigned int i;

	hw_nvn = readl(gdp->regs + GAM_GDP_NVN_OFFSET);
	if (!hw_nvn)
		goto end;

	for (i = 0; i < GDP_NODE_NB_BANK; i++)
		if ((hw_nvn != gdp->node_list[i].btm_field_paddr) &&
		    (hw_nvn != gdp->node_list[i].top_field_paddr))
			return &gdp->node_list[i];

	/* in hazardious cases restart with the first node */
	DRM_ERROR("inconsistent NVN for %s: 0x%08X\n",
			sti_plane_to_str(&gdp->plane), hw_nvn);

end:
	return &gdp->node_list[0];
}
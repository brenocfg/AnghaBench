#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  status; } ;
struct sti_gdp {int /*<<< orphan*/ * vtg; TYPE_4__ plane; scalar_t__ clk_pix; int /*<<< orphan*/  vtg_field_nb; TYPE_3__* node_list; } ;
struct TYPE_7__ {TYPE_2__* btm_field; TYPE_1__* top_field; } ;
struct TYPE_6__ {int /*<<< orphan*/  gam_gdp_ppt; } ;
struct TYPE_5__ {int /*<<< orphan*/  gam_gdp_ppt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int /*<<< orphan*/  GAM_GDP_PPT_IGNORE ; 
 unsigned int GDP_NODE_NB_BANK ; 
 int /*<<< orphan*/  STI_PLANE_DISABLED ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  sti_plane_to_str (TYPE_4__*) ; 
 scalar_t__ sti_vtg_unregister_client (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sti_gdp_disable(struct sti_gdp *gdp)
{
	unsigned int i;

	DRM_DEBUG_DRIVER("%s\n", sti_plane_to_str(&gdp->plane));

	/* Set the nodes as 'to be ignored on mixer' */
	for (i = 0; i < GDP_NODE_NB_BANK; i++) {
		gdp->node_list[i].top_field->gam_gdp_ppt |= GAM_GDP_PPT_IGNORE;
		gdp->node_list[i].btm_field->gam_gdp_ppt |= GAM_GDP_PPT_IGNORE;
	}

	if (sti_vtg_unregister_client(gdp->vtg, &gdp->vtg_field_nb))
		DRM_DEBUG_DRIVER("Warning: cannot unregister VTG notifier\n");

	if (gdp->clk_pix)
		clk_disable_unprepare(gdp->clk_pix);

	gdp->plane.status = STI_PLANE_DISABLED;
	gdp->vtg = NULL;
}
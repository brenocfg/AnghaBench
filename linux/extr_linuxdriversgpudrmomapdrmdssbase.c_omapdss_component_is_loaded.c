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
struct omapdss_comp_node {int /*<<< orphan*/  node; scalar_t__ dss_core_component; } ;

/* Variables and functions */
 scalar_t__ omapdss_component_is_display (int /*<<< orphan*/ ) ; 
 scalar_t__ omapdss_component_is_output (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool omapdss_component_is_loaded(struct omapdss_comp_node *comp)
{
	if (comp->dss_core_component)
		return true;
	if (omapdss_component_is_display(comp->node))
		return true;
	if (omapdss_component_is_output(comp->node))
		return true;

	return false;
}
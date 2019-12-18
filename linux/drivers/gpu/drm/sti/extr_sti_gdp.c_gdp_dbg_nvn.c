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
struct sti_gdp {TYPE_1__* node_list; } ;
struct seq_file {int dummy; } ;
struct TYPE_2__ {int top_field_paddr; int btm_field_paddr; void* btm_field; void* top_field; } ;

/* Variables and functions */
 unsigned int GDP_NODE_NB_BANK ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,void*) ; 

__attribute__((used)) static void gdp_dbg_nvn(struct seq_file *s, struct sti_gdp *gdp, int val)
{
	void *base = NULL;
	unsigned int i;

	for (i = 0; i < GDP_NODE_NB_BANK; i++) {
		if (gdp->node_list[i].top_field_paddr == val) {
			base = gdp->node_list[i].top_field;
			break;
		}
		if (gdp->node_list[i].btm_field_paddr == val) {
			base = gdp->node_list[i].btm_field;
			break;
		}
	}

	if (base)
		seq_printf(s, "\tVirt @: %p", base);
}
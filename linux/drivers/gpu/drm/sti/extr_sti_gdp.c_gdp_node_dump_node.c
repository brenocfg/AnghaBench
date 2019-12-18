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
struct sti_gdp_node {struct sti_gdp_node* gam_gdp_cml; struct sti_gdp_node* gam_gdp_ppt; struct sti_gdp_node* gam_gdp_key2; struct sti_gdp_node* gam_gdp_key1; struct sti_gdp_node* gam_gdp_nvn; struct sti_gdp_node* gam_gdp_size; struct sti_gdp_node* gam_gdp_pmp; struct sti_gdp_node* gam_gdp_pml; struct sti_gdp_node* gam_gdp_vps; struct sti_gdp_node* gam_gdp_vpo; struct sti_gdp_node* gam_gdp_agc; struct sti_gdp_node* gam_gdp_ctl; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdp_dbg_ctl (struct seq_file*,struct sti_gdp_node*) ; 
 int /*<<< orphan*/  gdp_dbg_ppt (struct seq_file*,struct sti_gdp_node*) ; 
 int /*<<< orphan*/  gdp_dbg_size (struct seq_file*,struct sti_gdp_node*) ; 
 int /*<<< orphan*/  gdp_dbg_vpo (struct seq_file*,struct sti_gdp_node*) ; 
 int /*<<< orphan*/  gdp_dbg_vps (struct seq_file*,struct sti_gdp_node*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,struct sti_gdp_node*) ; 

__attribute__((used)) static void gdp_node_dump_node(struct seq_file *s, struct sti_gdp_node *node)
{
	seq_printf(s, "\t@:0x%p", node);
	seq_printf(s, "\n\tCTL  0x%08X", node->gam_gdp_ctl);
	gdp_dbg_ctl(s, node->gam_gdp_ctl);
	seq_printf(s, "\n\tAGC  0x%08X", node->gam_gdp_agc);
	seq_printf(s, "\n\tVPO  0x%08X", node->gam_gdp_vpo);
	gdp_dbg_vpo(s, node->gam_gdp_vpo);
	seq_printf(s, "\n\tVPS  0x%08X", node->gam_gdp_vps);
	gdp_dbg_vps(s, node->gam_gdp_vps);
	seq_printf(s, "\n\tPML  0x%08X", node->gam_gdp_pml);
	seq_printf(s, "\n\tPMP  0x%08X", node->gam_gdp_pmp);
	seq_printf(s, "\n\tSIZE 0x%08X", node->gam_gdp_size);
	gdp_dbg_size(s, node->gam_gdp_size);
	seq_printf(s, "\n\tNVN  0x%08X", node->gam_gdp_nvn);
	seq_printf(s, "\n\tKEY1 0x%08X", node->gam_gdp_key1);
	seq_printf(s, "\n\tKEY2 0x%08X", node->gam_gdp_key2);
	seq_printf(s, "\n\tPPT  0x%08X", node->gam_gdp_ppt);
	gdp_dbg_ppt(s, node->gam_gdp_ppt);
	seq_printf(s, "\n\tCML  0x%08X\n", node->gam_gdp_cml);
}
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
struct seq_file {struct mvpp2_dbgfs_prs_entry* private; } ;
struct mvpp2_prs_entry {int dummy; } ;
struct mvpp2_dbgfs_prs_entry {int /*<<< orphan*/  tid; int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 unsigned int MVPP2_PRS_PORT_MASK ; 
 int /*<<< orphan*/  mvpp2_prs_init_from_hw (int /*<<< orphan*/ ,struct mvpp2_prs_entry*,int /*<<< orphan*/ ) ; 
 unsigned int mvpp2_prs_tcam_port_map_get (struct mvpp2_prs_entry*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned int) ; 

__attribute__((used)) static int mvpp2_dbgfs_prs_pmap_show(struct seq_file *s, void *unused)
{
	struct mvpp2_dbgfs_prs_entry *entry = s->private;
	struct mvpp2_prs_entry pe;
	unsigned int pmap;

	mvpp2_prs_init_from_hw(entry->priv, &pe, entry->tid);

	pmap = mvpp2_prs_tcam_port_map_get(&pe);
	pmap &= MVPP2_PRS_PORT_MASK;

	seq_printf(s, "%02x\n", pmap);

	return 0;
}
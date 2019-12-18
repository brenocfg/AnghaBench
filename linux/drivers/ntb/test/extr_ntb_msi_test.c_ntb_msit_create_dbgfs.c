#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct ntb_msit_ctx {TYPE_2__* isr_ctx; struct dentry* dbgfs_dir; TYPE_2__* peers; TYPE_1__* ntb; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int pidx; int /*<<< orphan*/  init_comp; struct ntb_msit_ctx* nm; } ;
struct TYPE_3__ {struct pci_dev* pdev; } ;

/* Variables and functions */
 void* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct ntb_msit_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file_unsafe (char*,int,struct dentry*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntb_msit_count_fops ; 
 struct dentry* ntb_msit_dbgfs_topdir ; 
 int /*<<< orphan*/  ntb_msit_local_port_fops ; 
 int /*<<< orphan*/  ntb_msit_occurrences_fops ; 
 int /*<<< orphan*/  ntb_msit_port_fops ; 
 int /*<<< orphan*/  ntb_msit_ready_fops ; 
 int /*<<< orphan*/  ntb_msit_trigger_fops ; 
 int ntb_peer_port_count (TYPE_1__*) ; 
 int num_irqs ; 
 char* pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void ntb_msit_create_dbgfs(struct ntb_msit_ctx *nm)
{
	struct pci_dev *pdev = nm->ntb->pdev;
	char buf[32];
	int i;
	struct dentry *peer_dir;

	nm->dbgfs_dir = debugfs_create_dir(pci_name(pdev),
					   ntb_msit_dbgfs_topdir);
	debugfs_create_file("port", 0400, nm->dbgfs_dir, nm,
			    &ntb_msit_local_port_fops);

	for (i = 0; i < ntb_peer_port_count(nm->ntb); i++) {
		nm->peers[i].pidx = i;
		nm->peers[i].nm = nm;
		init_completion(&nm->peers[i].init_comp);

		snprintf(buf, sizeof(buf), "peer%d", i);
		peer_dir = debugfs_create_dir(buf, nm->dbgfs_dir);

		debugfs_create_file_unsafe("trigger", 0200, peer_dir,
					   &nm->peers[i],
					   &ntb_msit_trigger_fops);

		debugfs_create_file_unsafe("port", 0400, peer_dir,
					   &nm->peers[i], &ntb_msit_port_fops);

		debugfs_create_file_unsafe("count", 0400, peer_dir,
					   &nm->peers[i],
					   &ntb_msit_count_fops);

		debugfs_create_file_unsafe("ready", 0600, peer_dir,
					   &nm->peers[i],
					   &ntb_msit_ready_fops);
	}

	for (i = 0; i < num_irqs; i++) {
		snprintf(buf, sizeof(buf), "irq%d_occurrences", i);
		debugfs_create_file_unsafe(buf, 0400, nm->dbgfs_dir,
					   &nm->isr_ctx[i],
					   &ntb_msit_occurrences_fops);
	}
}
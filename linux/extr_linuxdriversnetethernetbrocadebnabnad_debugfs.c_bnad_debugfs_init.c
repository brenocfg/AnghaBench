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
struct bnad_debugfs_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  fops; int /*<<< orphan*/  mode; } ;
struct bnad {int /*<<< orphan*/  netdev; int /*<<< orphan*/ * bnad_dentry_files; void* port_debugfs_root; int /*<<< orphan*/  pcidev; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int ARRAY_SIZE (struct bnad_debugfs_entry*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_debugfs_port_count ; 
 int /*<<< orphan*/ * bna_debugfs_root ; 
 struct bnad_debugfs_entry* bnad_debugfs_files ; 
 void* debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,struct bnad*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,...) ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

void
bnad_debugfs_init(struct bnad *bnad)
{
	const struct bnad_debugfs_entry *file;
	char name[64];
	int i;

	/* Setup the BNA debugfs root directory*/
	if (!bna_debugfs_root) {
		bna_debugfs_root = debugfs_create_dir("bna", NULL);
		atomic_set(&bna_debugfs_port_count, 0);
		if (!bna_debugfs_root) {
			netdev_warn(bnad->netdev,
				    "debugfs root dir creation failed\n");
			return;
		}
	}

	/* Setup the pci_dev debugfs directory for the port */
	snprintf(name, sizeof(name), "pci_dev:%s", pci_name(bnad->pcidev));
	if (!bnad->port_debugfs_root) {
		bnad->port_debugfs_root =
			debugfs_create_dir(name, bna_debugfs_root);
		if (!bnad->port_debugfs_root) {
			netdev_warn(bnad->netdev,
				    "debugfs root dir creation failed\n");
			return;
		}

		atomic_inc(&bna_debugfs_port_count);

		for (i = 0; i < ARRAY_SIZE(bnad_debugfs_files); i++) {
			file = &bnad_debugfs_files[i];
			bnad->bnad_dentry_files[i] =
					debugfs_create_file(file->name,
							file->mode,
							bnad->port_debugfs_root,
							bnad,
							file->fops);
			if (!bnad->bnad_dentry_files[i]) {
				netdev_warn(bnad->netdev,
					    "create %s entry failed\n",
					    file->name);
				return;
			}
		}
	}
}
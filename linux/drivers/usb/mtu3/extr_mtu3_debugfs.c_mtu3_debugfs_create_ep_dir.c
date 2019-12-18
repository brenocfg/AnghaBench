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
struct mtu3_file_map {int /*<<< orphan*/  name; } ;
struct mtu3_ep {int /*<<< orphan*/  mtu; int /*<<< orphan*/  name; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct mtu3_file_map*) ; 
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int,struct dentry*,struct mtu3_ep*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtu3_debugfs_ep_regset (int /*<<< orphan*/ ,struct mtu3_ep*,struct dentry*) ; 
 struct mtu3_file_map* mtu3_ep_files ; 
 int /*<<< orphan*/  mtu3_ep_fops ; 

__attribute__((used)) static void mtu3_debugfs_create_ep_dir(struct mtu3_ep *mep,
				       struct dentry *parent)
{
	const struct mtu3_file_map *files;
	struct dentry *dir_ep;
	int i;

	dir_ep = debugfs_create_dir(mep->name, parent);
	mtu3_debugfs_ep_regset(mep->mtu, mep, dir_ep);

	for (i = 0; i < ARRAY_SIZE(mtu3_ep_files); i++) {
		files = &mtu3_ep_files[i];

		debugfs_create_file(files->name, 0444, dir_ep,
				    mep, &mtu3_ep_fops);
	}
}
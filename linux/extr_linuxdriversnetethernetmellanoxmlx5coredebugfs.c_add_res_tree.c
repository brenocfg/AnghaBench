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
struct mlx5_rsc_debug {int type; int /*<<< orphan*/  root; TYPE_1__* fields; void* object; struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int dummy; } ;
struct dentry {int dummy; } ;
typedef  enum dbg_rsc_type { ____Placeholder_dbg_rsc_type } dbg_rsc_type ;
struct TYPE_2__ {int i; int /*<<< orphan*/  dent; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fields ; 
 int /*<<< orphan*/  fops ; 
 int /*<<< orphan*/  kfree (struct mlx5_rsc_debug*) ; 
 struct mlx5_rsc_debug* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  struct_size (struct mlx5_rsc_debug*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int add_res_tree(struct mlx5_core_dev *dev, enum dbg_rsc_type type,
			struct dentry *root, struct mlx5_rsc_debug **dbg,
			int rsn, char **field, int nfile, void *data)
{
	struct mlx5_rsc_debug *d;
	char resn[32];
	int err;
	int i;

	d = kzalloc(struct_size(d, fields, nfile), GFP_KERNEL);
	if (!d)
		return -ENOMEM;

	d->dev = dev;
	d->object = data;
	d->type = type;
	sprintf(resn, "0x%x", rsn);
	d->root = debugfs_create_dir(resn,  root);
	if (!d->root) {
		err = -ENOMEM;
		goto out_free;
	}

	for (i = 0; i < nfile; i++) {
		d->fields[i].i = i;
		d->fields[i].dent = debugfs_create_file(field[i], 0400,
							d->root, &d->fields[i],
							&fops);
		if (!d->fields[i].dent) {
			err = -ENOMEM;
			goto out_rem;
		}
	}
	*dbg = d;

	return 0;
out_rem:
	debugfs_remove_recursive(d->root);

out_free:
	kfree(d);
	return err;
}
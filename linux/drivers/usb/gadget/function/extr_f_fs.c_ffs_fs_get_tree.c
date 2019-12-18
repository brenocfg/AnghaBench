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
struct fs_context {int /*<<< orphan*/  source; struct ffs_sb_fill_data* fs_private; } ;
struct ffs_sb_fill_data {struct ffs_data* ffs_data; int /*<<< orphan*/  no_disconnect; int /*<<< orphan*/  perms; } ;
struct ffs_data {void* private_data; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  no_disconnect; int /*<<< orphan*/  file_perms; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* ffs_acquire_dev (int /*<<< orphan*/ ) ; 
 struct ffs_data* ffs_data_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffs_data_put (struct ffs_data*) ; 
 int /*<<< orphan*/  ffs_sb_fill ; 
 int get_tree_nodev (struct fs_context*,int /*<<< orphan*/ ) ; 
 int invalf (struct fs_context*,char*) ; 
 int /*<<< orphan*/  kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ffs_fs_get_tree(struct fs_context *fc)
{
	struct ffs_sb_fill_data *ctx = fc->fs_private;
	void *ffs_dev;
	struct ffs_data	*ffs;

	ENTER();

	if (!fc->source)
		return invalf(fc, "No source specified");

	ffs = ffs_data_new(fc->source);
	if (unlikely(!ffs))
		return -ENOMEM;
	ffs->file_perms = ctx->perms;
	ffs->no_disconnect = ctx->no_disconnect;

	ffs->dev_name = kstrdup(fc->source, GFP_KERNEL);
	if (unlikely(!ffs->dev_name)) {
		ffs_data_put(ffs);
		return -ENOMEM;
	}

	ffs_dev = ffs_acquire_dev(ffs->dev_name);
	if (IS_ERR(ffs_dev)) {
		ffs_data_put(ffs);
		return PTR_ERR(ffs_dev);
	}

	ffs->private_data = ffs_dev;
	ctx->ffs_data = ffs;
	return get_tree_nodev(fc, ffs_sb_fill);
}
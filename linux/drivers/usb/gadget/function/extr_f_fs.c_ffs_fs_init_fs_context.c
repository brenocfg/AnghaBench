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
struct fs_context {int /*<<< orphan*/ * ops; struct ffs_sb_fill_data* fs_private; } ;
struct TYPE_2__ {int mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct ffs_sb_fill_data {int root_mode; int no_disconnect; TYPE_1__ perms; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 int /*<<< orphan*/  ffs_fs_context_ops ; 
 struct ffs_sb_fill_data* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ffs_fs_init_fs_context(struct fs_context *fc)
{
	struct ffs_sb_fill_data *ctx;

	ctx = kzalloc(sizeof(struct ffs_sb_fill_data), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->perms.mode = S_IFREG | 0600;
	ctx->perms.uid = GLOBAL_ROOT_UID;
	ctx->perms.gid = GLOBAL_ROOT_GID;
	ctx->root_mode = S_IFDIR | 0500;
	ctx->no_disconnect = false;

	fc->fs_private = ctx;
	fc->ops = &ffs_fs_context_ops;
	return 0;
}
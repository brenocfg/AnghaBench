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
struct fs_context {struct ffs_sb_fill_data* fs_private; } ;
struct ffs_sb_fill_data {scalar_t__ ffs_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ffs_data_put (scalar_t__) ; 
 int /*<<< orphan*/  ffs_release_dev (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ffs_sb_fill_data*) ; 

__attribute__((used)) static void ffs_fs_free_fc(struct fs_context *fc)
{
	struct ffs_sb_fill_data *ctx = fc->fs_private;

	if (ctx) {
		if (ctx->ffs_data) {
			ffs_release_dev(ctx->ffs_data);
			ffs_data_put(ctx->ffs_data);
		}

		kfree(ctx);
	}
}
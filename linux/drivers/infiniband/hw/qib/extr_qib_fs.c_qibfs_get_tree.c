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
struct fs_context {TYPE_1__* root; } ;
struct TYPE_2__ {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int get_tree_single (struct fs_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_super ; 
 int /*<<< orphan*/  qibfs_fill_super ; 

__attribute__((used)) static int qibfs_get_tree(struct fs_context *fc)
{
	int ret = get_tree_single(fc, qibfs_fill_super);
	if (ret == 0)
		qib_super = fc->root->d_sb;
	return ret;
}
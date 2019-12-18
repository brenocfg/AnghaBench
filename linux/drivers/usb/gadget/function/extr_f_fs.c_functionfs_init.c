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

/* Variables and functions */
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  ffs_fs_type ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int register_filesystem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int functionfs_init(void)
{
	int ret;

	ENTER();

	ret = register_filesystem(&ffs_fs_type);
	if (likely(!ret))
		pr_info("file system registered\n");
	else
		pr_err("failed registering file system (%d)\n", ret);

	return ret;
}
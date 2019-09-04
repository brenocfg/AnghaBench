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
struct binder_alloc {int /*<<< orphan*/  vma; } ;

/* Variables and functions */
 int BUFFER_NUM ; 
 int /*<<< orphan*/  binder_selftest_alloc_offset (struct binder_alloc*,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ binder_selftest_failures ; 
 int /*<<< orphan*/  binder_selftest_lock ; 
 int binder_selftest_run ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

void binder_selftest_alloc(struct binder_alloc *alloc)
{
	size_t end_offset[BUFFER_NUM];

	if (!binder_selftest_run)
		return;
	mutex_lock(&binder_selftest_lock);
	if (!binder_selftest_run || !alloc->vma)
		goto done;
	pr_info("STARTED\n");
	binder_selftest_alloc_offset(alloc, end_offset, 0);
	binder_selftest_run = false;
	if (binder_selftest_failures > 0)
		pr_info("%d tests FAILED\n", binder_selftest_failures);
	else
		pr_info("PASSED\n");

done:
	mutex_unlock(&binder_selftest_lock);
}
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
struct pblk {int /*<<< orphan*/  pad_wa; int /*<<< orphan*/  gc_wa; int /*<<< orphan*/  user_wa; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_get_write_amp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t pblk_sysfs_get_write_amp_mileage(struct pblk *pblk, char *page)
{
	return pblk_get_write_amp(atomic64_read(&pblk->user_wa),
		atomic64_read(&pblk->gc_wa), atomic64_read(&pblk->pad_wa),
		page);
}
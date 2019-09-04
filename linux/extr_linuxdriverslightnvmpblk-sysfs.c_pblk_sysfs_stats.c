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
struct pblk {int /*<<< orphan*/  erase_failed; int /*<<< orphan*/  write_failed; int /*<<< orphan*/  read_failed_gc; int /*<<< orphan*/  read_empty; int /*<<< orphan*/  read_high_ecc; int /*<<< orphan*/  read_failed; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t pblk_sysfs_stats(struct pblk *pblk, char *page)
{
	ssize_t sz;

	sz = snprintf(page, PAGE_SIZE,
			"read_failed=%lu, read_high_ecc=%lu, read_empty=%lu, read_failed_gc=%lu, write_failed=%lu, erase_failed=%lu\n",
			atomic_long_read(&pblk->read_failed),
			atomic_long_read(&pblk->read_high_ecc),
			atomic_long_read(&pblk->read_empty),
			atomic_long_read(&pblk->read_failed_gc),
			atomic_long_read(&pblk->write_failed),
			atomic_long_read(&pblk->erase_failed));

	return sz;
}
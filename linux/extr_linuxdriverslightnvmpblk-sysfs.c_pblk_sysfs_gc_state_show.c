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
struct pblk {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  pblk_gc_sysfs_state_show (struct pblk*,int*,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static ssize_t pblk_sysfs_gc_state_show(struct pblk *pblk, char *page)
{
	int gc_enabled, gc_active;

	pblk_gc_sysfs_state_show(pblk, &gc_enabled, &gc_active);
	return snprintf(page, PAGE_SIZE, "gc_enabled=%d, gc_active=%d\n",
					gc_enabled, gc_active);
}
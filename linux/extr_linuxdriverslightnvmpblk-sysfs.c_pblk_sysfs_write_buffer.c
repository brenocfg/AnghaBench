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
struct pblk {int /*<<< orphan*/  rwb; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  pblk_rb_sysfs (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static ssize_t pblk_sysfs_write_buffer(struct pblk *pblk, char *page)
{
	return pblk_rb_sysfs(&pblk->rwb, page);
}
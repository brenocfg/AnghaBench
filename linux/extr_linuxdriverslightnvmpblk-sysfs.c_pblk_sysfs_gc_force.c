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
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ kstrtouint (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pblk_gc_sysfs_force (struct pblk*,int) ; 
 size_t strcspn (char const*,char*) ; 

__attribute__((used)) static ssize_t pblk_sysfs_gc_force(struct pblk *pblk, const char *page,
				   size_t len)
{
	size_t c_len;
	int force;

	c_len = strcspn(page, "\n");
	if (c_len >= len)
		return -EINVAL;

	if (kstrtouint(page, 0, &force))
		return -EINVAL;

	pblk_gc_sysfs_force(pblk, force);

	return len;
}
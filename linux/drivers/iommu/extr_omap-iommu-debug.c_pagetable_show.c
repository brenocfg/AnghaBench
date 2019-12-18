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
struct seq_file {struct omap_iommu* private; } ;
struct omap_iommu {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  dump_ioptable (struct seq_file*) ; 
 int /*<<< orphan*/  iommu_debug_lock ; 
 scalar_t__ is_omap_iommu_detached (struct omap_iommu*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,char*) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int pagetable_show(struct seq_file *s, void *data)
{
	struct omap_iommu *obj = s->private;

	if (is_omap_iommu_detached(obj))
		return -EPERM;

	mutex_lock(&iommu_debug_lock);

	seq_printf(s, "L: %8s %8s\n", "da:", "pte:");
	seq_puts(s, "--------------------------\n");
	dump_ioptable(s);

	mutex_unlock(&iommu_debug_lock);

	return 0;
}
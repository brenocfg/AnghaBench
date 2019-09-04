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
struct gart_device {int /*<<< orphan*/  pte_lock; int /*<<< orphan*/  savedata; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct gart_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  do_gart_setup (struct gart_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int tegra_gart_resume(struct device *dev)
{
	struct gart_device *gart = dev_get_drvdata(dev);
	unsigned long flags;

	spin_lock_irqsave(&gart->pte_lock, flags);
	do_gart_setup(gart, gart->savedata);
	spin_unlock_irqrestore(&gart->pte_lock, flags);
	return 0;
}
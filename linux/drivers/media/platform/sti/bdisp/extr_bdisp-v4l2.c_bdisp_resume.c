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
struct device {int dummy; } ;
struct bdisp_dev {int /*<<< orphan*/  slock; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_M2M_OPEN ; 
 int bdisp_runtime_resume (struct device*) ; 
 struct bdisp_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_suspended (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bdisp_resume(struct device *dev)
{
	struct bdisp_dev *bdisp = dev_get_drvdata(dev);
	unsigned long flags;
	int opened;

	spin_lock_irqsave(&bdisp->slock, flags);
	opened = test_bit(ST_M2M_OPEN, &bdisp->state);
	spin_unlock_irqrestore(&bdisp->slock, flags);

	if (!opened)
		return 0;

	if (!pm_runtime_suspended(dev))
		return bdisp_runtime_resume(dev);

	return 0;
}
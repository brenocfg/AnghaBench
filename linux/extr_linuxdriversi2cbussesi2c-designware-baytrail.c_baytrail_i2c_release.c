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
struct dw_i2c_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  acquire_lock; } ;

/* Variables and functions */
 scalar_t__ acquired ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  reset_semaphore (struct dw_i2c_dev*) ; 

__attribute__((used)) static void baytrail_i2c_release(struct dw_i2c_dev *dev)
{
	if (!dev || !dev->dev)
		return;

	if (!dev->acquire_lock)
		return;

	reset_semaphore(dev);
	dev_dbg(dev->dev, "punit semaphore held for %ums\n",
		jiffies_to_msecs(jiffies - acquired));
}
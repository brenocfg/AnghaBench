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
typedef  scalar_t__ u32 ;
struct dw_i2c_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  pm_qos; int /*<<< orphan*/  release_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MBI_UNIT_PMC ; 
 int ENODEV ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MBI_PMIC_BUS_ACCESS_BEGIN ; 
 int /*<<< orphan*/  MBI_REG_READ ; 
 int /*<<< orphan*/  MBI_REG_WRITE ; 
 scalar_t__ PUNIT_SEMAPHORE_ACQUIRE ; 
 int /*<<< orphan*/  SEMAPHORE_TIMEOUT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned long acquired ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int get_sem (struct dw_i2c_dev*,scalar_t__*) ; 
 scalar_t__ get_sem_addr (struct dw_i2c_dev*) ; 
 int /*<<< orphan*/  iosf_mbi_call_pmic_bus_access_notifier_chain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iosf_mbi_punit_acquire () ; 
 int iosf_mbi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int iosf_mbi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  might_sleep () ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_qos_update_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_semaphore (struct dw_i2c_dev*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int baytrail_i2c_acquire(struct dw_i2c_dev *dev)
{
	u32 addr;
	u32 sem = PUNIT_SEMAPHORE_ACQUIRE;
	int ret;
	unsigned long start, end;

	might_sleep();

	if (!dev || !dev->dev)
		return -ENODEV;

	if (!dev->release_lock)
		return 0;

	iosf_mbi_punit_acquire();
	iosf_mbi_call_pmic_bus_access_notifier_chain(MBI_PMIC_BUS_ACCESS_BEGIN,
						     NULL);

	/*
	 * Disallow the CPU to enter C6 or C7 state, entering these states
	 * requires the punit to talk to the pmic and if this happens while
	 * we're holding the semaphore, the SoC hangs.
	 */
	pm_qos_update_request(&dev->pm_qos, 0);

	addr = get_sem_addr(dev);

	/* host driver writes to side band semaphore register */
	ret = iosf_mbi_write(BT_MBI_UNIT_PMC, MBI_REG_WRITE, addr, sem);
	if (ret) {
		dev_err(dev->dev, "iosf punit semaphore request failed\n");
		goto out;
	}

	/* host driver waits for bit 0 to be set in semaphore register */
	start = jiffies;
	end = start + msecs_to_jiffies(SEMAPHORE_TIMEOUT);
	do {
		ret = get_sem(dev, &sem);
		if (!ret && sem) {
			acquired = jiffies;
			dev_dbg(dev->dev, "punit semaphore acquired after %ums\n",
				jiffies_to_msecs(jiffies - start));
			return 0;
		}

		usleep_range(1000, 2000);
	} while (time_before(jiffies, end));

	dev_err(dev->dev, "punit semaphore timed out, resetting\n");
out:
	reset_semaphore(dev);

	ret = iosf_mbi_read(BT_MBI_UNIT_PMC, MBI_REG_READ, addr, &sem);
	if (ret)
		dev_err(dev->dev, "iosf failed to read punit semaphore\n");
	else
		dev_err(dev->dev, "PUNIT SEM: %d\n", sem);

	WARN_ON(1);

	return -ETIMEDOUT;
}
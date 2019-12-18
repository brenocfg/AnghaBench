#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct bcm2835_power_domain {TYPE_1__ base; struct bcm2835_power* power; } ;
struct bcm2835_power {struct device* dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int PM_INRUSH_20_MA ; 
 int PM_INRUSH_3_5_MA ; 
 int PM_INRUSH_MASK ; 
 int PM_INRUSH_SHIFT ; 
 int PM_ISFUNC ; 
 int PM_ISPOW ; 
 int PM_MEMREP ; 
 int PM_MRDONE ; 
 int PM_POWOK ; 
 int PM_POWUP ; 
 int PM_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int ktime_get_ns () ; 

__attribute__((used)) static int bcm2835_power_power_on(struct bcm2835_power_domain *pd, u32 pm_reg)
{
	struct bcm2835_power *power = pd->power;
	struct device *dev = power->dev;
	u64 start;
	int ret;
	int inrush;
	bool powok;

	/* If it was already powered on by the fw, leave it that way. */
	if (PM_READ(pm_reg) & PM_POWUP)
		return 0;

	/* Enable power.  Allowing too much current at once may result
	 * in POWOK never getting set, so start low and ramp it up as
	 * necessary to succeed.
	 */
	powok = false;
	for (inrush = PM_INRUSH_3_5_MA; inrush <= PM_INRUSH_20_MA; inrush++) {
		PM_WRITE(pm_reg,
			 (PM_READ(pm_reg) & ~PM_INRUSH_MASK) |
			 (inrush << PM_INRUSH_SHIFT) |
			 PM_POWUP);

		start = ktime_get_ns();
		while (!(powok = !!(PM_READ(pm_reg) & PM_POWOK))) {
			cpu_relax();
			if (ktime_get_ns() - start >= 3000)
				break;
		}
	}
	if (!powok) {
		dev_err(dev, "Timeout waiting for %s power OK\n",
			pd->base.name);
		ret = -ETIMEDOUT;
		goto err_disable_powup;
	}

	/* Disable electrical isolation */
	PM_WRITE(pm_reg, PM_READ(pm_reg) | PM_ISPOW);

	/* Repair memory */
	PM_WRITE(pm_reg, PM_READ(pm_reg) | PM_MEMREP);
	start = ktime_get_ns();
	while (!(PM_READ(pm_reg) & PM_MRDONE)) {
		cpu_relax();
		if (ktime_get_ns() - start >= 1000) {
			dev_err(dev, "Timeout waiting for %s memory repair\n",
				pd->base.name);
			ret = -ETIMEDOUT;
			goto err_disable_ispow;
		}
	}

	/* Disable functional isolation */
	PM_WRITE(pm_reg, PM_READ(pm_reg) | PM_ISFUNC);

	return 0;

err_disable_ispow:
	PM_WRITE(pm_reg, PM_READ(pm_reg) & ~PM_ISPOW);
err_disable_powup:
	PM_WRITE(pm_reg, PM_READ(pm_reg) & ~(PM_POWUP | PM_INRUSH_MASK));
	return ret;
}
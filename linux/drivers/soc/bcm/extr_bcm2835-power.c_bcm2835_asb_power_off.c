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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct bcm2835_power_domain {int /*<<< orphan*/  clk; TYPE_1__ base; struct bcm2835_power* power; } ;
struct bcm2835_power {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PM_READ (int) ; 
 int /*<<< orphan*/  PM_WRITE (int,int) ; 
 int bcm2835_asb_disable (struct bcm2835_power*,int) ; 
 int /*<<< orphan*/  bcm2835_asb_enable (struct bcm2835_power*,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm2835_asb_power_off(struct bcm2835_power_domain *pd,
				 u32 pm_reg,
				 u32 asb_m_reg,
				 u32 asb_s_reg,
				 u32 reset_flags)
{
	struct bcm2835_power *power = pd->power;
	int ret;

	ret = bcm2835_asb_disable(power, asb_s_reg);
	if (ret) {
		dev_warn(power->dev, "Failed to disable ASB slave for %s\n",
			 pd->base.name);
		return ret;
	}
	ret = bcm2835_asb_disable(power, asb_m_reg);
	if (ret) {
		dev_warn(power->dev, "Failed to disable ASB master for %s\n",
			 pd->base.name);
		bcm2835_asb_enable(power, asb_s_reg);
		return ret;
	}

	clk_disable_unprepare(pd->clk);

	/* Assert the resets. */
	PM_WRITE(pm_reg, PM_READ(pm_reg) & ~reset_flags);

	return 0;
}
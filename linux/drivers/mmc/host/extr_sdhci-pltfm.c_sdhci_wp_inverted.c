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

/* Variables and functions */
 scalar_t__ device_property_present (struct device*,char*) ; 
 scalar_t__ machine_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc837x_mds ; 
 int /*<<< orphan*/  mpc837x_rdb ; 

__attribute__((used)) static bool sdhci_wp_inverted(struct device *dev)
{
	if (device_property_present(dev, "sdhci,wp-inverted") ||
	    device_property_present(dev, "wp-inverted"))
		return true;

	/* Old device trees don't have the wp-inverted property. */
#ifdef CONFIG_PPC
	return machine_is(mpc837x_rdb) || machine_is(mpc837x_mds);
#else
	return false;
#endif /* CONFIG_PPC */
}
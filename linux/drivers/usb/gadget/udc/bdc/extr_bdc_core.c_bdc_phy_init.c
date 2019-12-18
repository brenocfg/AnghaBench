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
struct bdc {int num_phys; int /*<<< orphan*/ * phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int phy_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 int phy_power_on (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bdc_phy_init(struct bdc *bdc)
{
	int phy_num;
	int ret;

	for (phy_num = 0; phy_num < bdc->num_phys; phy_num++) {
		ret = phy_init(bdc->phys[phy_num]);
		if (ret)
			goto err_exit_phy;
		ret = phy_power_on(bdc->phys[phy_num]);
		if (ret) {
			phy_exit(bdc->phys[phy_num]);
			goto err_exit_phy;
		}
	}

	return 0;

err_exit_phy:
	while (--phy_num >= 0) {
		phy_power_off(bdc->phys[phy_num]);
		phy_exit(bdc->phys[phy_num]);
	}

	return ret;
}
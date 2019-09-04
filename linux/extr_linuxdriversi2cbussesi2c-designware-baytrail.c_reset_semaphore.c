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
struct dw_i2c_dev {int /*<<< orphan*/  pm_qos; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MBI_UNIT_PMC ; 
 int /*<<< orphan*/  MBI_PMIC_BUS_ACCESS_END ; 
 int /*<<< orphan*/  MBI_REG_READ ; 
 int /*<<< orphan*/  PM_QOS_DEFAULT_VALUE ; 
 int /*<<< orphan*/  PUNIT_SEMAPHORE_BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_sem_addr (struct dw_i2c_dev*) ; 
 int /*<<< orphan*/  iosf_mbi_call_pmic_bus_access_notifier_chain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ iosf_mbi_modify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iosf_mbi_punit_release () ; 
 int /*<<< orphan*/  pm_qos_update_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_semaphore(struct dw_i2c_dev *dev)
{
	if (iosf_mbi_modify(BT_MBI_UNIT_PMC, MBI_REG_READ, get_sem_addr(dev),
			    0, PUNIT_SEMAPHORE_BIT))
		dev_err(dev->dev, "iosf failed to reset punit semaphore during write\n");

	pm_qos_update_request(&dev->pm_qos, PM_QOS_DEFAULT_VALUE);

	iosf_mbi_call_pmic_bus_access_notifier_chain(MBI_PMIC_BUS_ACCESS_END,
						     NULL);
	iosf_mbi_punit_release();
}
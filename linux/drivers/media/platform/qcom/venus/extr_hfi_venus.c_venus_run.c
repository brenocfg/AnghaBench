#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int da; } ;
struct TYPE_6__ {int da; } ;
struct venus_hfi_device {TYPE_1__ sfr; TYPE_3__ ifaceq_table; TYPE_2__* core; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CS_SCIACMDARG1 ; 
 int /*<<< orphan*/  CPU_CS_SCIACMDARG2 ; 
 int /*<<< orphan*/  SFR_ADDR ; 
 int SHARED_QSIZE ; 
 int /*<<< orphan*/  UC_REGION_ADDR ; 
 int /*<<< orphan*/  UC_REGION_SIZE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int venus_boot_core (struct venus_hfi_device*) ; 
 int /*<<< orphan*/  venus_hwversion (struct venus_hfi_device*) ; 
 int /*<<< orphan*/  venus_set_registers (struct venus_hfi_device*) ; 
 int /*<<< orphan*/  venus_writel (struct venus_hfi_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int venus_run(struct venus_hfi_device *hdev)
{
	struct device *dev = hdev->core->dev;
	int ret;

	/*
	 * Re-program all of the registers that get reset as a result of
	 * regulator_disable() and _enable()
	 */
	venus_set_registers(hdev);

	venus_writel(hdev, UC_REGION_ADDR, hdev->ifaceq_table.da);
	venus_writel(hdev, UC_REGION_SIZE, SHARED_QSIZE);
	venus_writel(hdev, CPU_CS_SCIACMDARG2, hdev->ifaceq_table.da);
	venus_writel(hdev, CPU_CS_SCIACMDARG1, 0x01);
	if (hdev->sfr.da)
		venus_writel(hdev, SFR_ADDR, hdev->sfr.da);

	ret = venus_boot_core(hdev);
	if (ret) {
		dev_err(dev, "failed to reset venus core\n");
		return ret;
	}

	venus_hwversion(hdev);

	return 0;
}
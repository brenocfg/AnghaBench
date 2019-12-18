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
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct idt_ntb_dev {TYPE_2__ ntb; TYPE_3__* swcfg; int /*<<< orphan*/  hwmon_mtx; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDT_SW_TMPCTL ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct device* devm_hwmon_device_register_with_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct idt_ntb_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idt_sw_write (struct idt_ntb_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  idt_temp_groups ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void idt_init_temp(struct idt_ntb_dev *ndev)
{
	struct device *hwmon;

	/* Enable sensor if it hasn't been already */
	idt_sw_write(ndev, IDT_SW_TMPCTL, 0x0);

	/* Initialize hwmon interface fields */
	mutex_init(&ndev->hwmon_mtx);

	hwmon = devm_hwmon_device_register_with_groups(&ndev->ntb.pdev->dev,
		ndev->swcfg->name, ndev, idt_temp_groups);
	if (IS_ERR(hwmon)) {
		dev_err(&ndev->ntb.pdev->dev, "Couldn't create hwmon device");
		return;
	}

	dev_dbg(&ndev->ntb.pdev->dev, "Temperature HWmon interface registered");
}
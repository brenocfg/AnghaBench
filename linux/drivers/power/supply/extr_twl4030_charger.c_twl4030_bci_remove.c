#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct twl4030_bci {TYPE_2__* ac; TYPE_1__* usb; } ;
struct platform_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL4030_INTERRUPTS_BCIIMR1A ; 
 int /*<<< orphan*/  TWL4030_INTERRUPTS_BCIIMR2A ; 
 int /*<<< orphan*/  TWL4030_MODULE_INTERRUPTS ; 
 int /*<<< orphan*/  dev_attr_mode ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct twl4030_bci* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  twl4030_charger_enable_ac (struct twl4030_bci*,int) ; 
 int /*<<< orphan*/  twl4030_charger_enable_backup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl4030_charger_enable_usb (struct twl4030_bci*,int) ; 
 int /*<<< orphan*/  twl_i2c_write_u8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_bci_remove(struct platform_device *pdev)
{
	struct twl4030_bci *bci = platform_get_drvdata(pdev);

	twl4030_charger_enable_ac(bci, false);
	twl4030_charger_enable_usb(bci, false);
	twl4030_charger_enable_backup(0, 0);

	device_remove_file(&bci->usb->dev, &dev_attr_mode);
	device_remove_file(&bci->ac->dev, &dev_attr_mode);
	/* mask interrupts */
	twl_i2c_write_u8(TWL4030_MODULE_INTERRUPTS, 0xff,
			 TWL4030_INTERRUPTS_BCIIMR1A);
	twl_i2c_write_u8(TWL4030_MODULE_INTERRUPTS, 0xff,
			 TWL4030_INTERRUPTS_BCIIMR2A);

	return 0;
}
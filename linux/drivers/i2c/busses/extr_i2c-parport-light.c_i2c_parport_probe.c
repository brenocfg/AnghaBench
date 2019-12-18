#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_11__ {scalar_t__ val; } ;
struct TYPE_14__ {scalar_t__ smbus_alert; TYPE_2__ init; } ;
struct TYPE_13__ {scalar_t__ irq; } ;
struct TYPE_10__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_12__ {TYPE_1__ dev; } ;

/* Variables and functions */
 TYPE_9__* adapter_parm ; 
 TYPE_6__ alert_data ; 
 scalar_t__ ara ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int i2c_bit_add_bus (TYPE_3__*) ; 
 scalar_t__ i2c_setup_smbus_alert (TYPE_3__*,TYPE_6__*) ; 
 scalar_t__ irq ; 
 int /*<<< orphan*/  line_set (int,TYPE_2__*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 TYPE_3__ parport_adapter ; 
 TYPE_2__ parport_ctrl_irq ; 
 int /*<<< orphan*/  parport_setscl (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  parport_setsda (int /*<<< orphan*/ *,int) ; 
 size_t type ; 

__attribute__((used)) static int i2c_parport_probe(struct platform_device *pdev)
{
	int err;

	/* Reset hardware to a sane state (SCL and SDA high) */
	parport_setsda(NULL, 1);
	parport_setscl(NULL, 1);
	/* Other init if needed (power on...) */
	if (adapter_parm[type].init.val) {
		line_set(1, &adapter_parm[type].init);
		/* Give powered devices some time to settle */
		msleep(100);
	}

	parport_adapter.dev.parent = &pdev->dev;
	err = i2c_bit_add_bus(&parport_adapter);
	if (err) {
		dev_err(&pdev->dev, "Unable to register with I2C\n");
		return err;
	}

	/* Setup SMBus alert if supported */
	if (adapter_parm[type].smbus_alert && irq) {
		alert_data.irq = irq;
		ara = i2c_setup_smbus_alert(&parport_adapter, &alert_data);
		if (ara)
			line_set(1, &parport_ctrl_irq);
		else
			dev_warn(&pdev->dev, "Failed to register ARA client\n");
	}

	return 0;
}
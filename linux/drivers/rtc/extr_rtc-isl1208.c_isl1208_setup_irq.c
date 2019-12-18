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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ driver; } ;

/* Variables and functions */
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct i2c_client*) ; 
 int /*<<< orphan*/  enable_irq_wake (int) ; 
 TYPE_2__ isl1208_driver ; 
 int /*<<< orphan*/  isl1208_rtc_interrupt ; 

__attribute__((used)) static int isl1208_setup_irq(struct i2c_client *client, int irq)
{
	int rc = devm_request_threaded_irq(&client->dev, irq, NULL,
					isl1208_rtc_interrupt,
					IRQF_SHARED | IRQF_ONESHOT,
					isl1208_driver.driver.name,
					client);
	if (!rc) {
		device_init_wakeup(&client->dev, 1);
		enable_irq_wake(irq);
	} else {
		dev_err(&client->dev,
			"Unable to request irq %d, no alarm support\n",
			irq);
	}
	return rc;
}
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
struct i2c_client {int dummy; } ;
struct bq25890_device {int /*<<< orphan*/  usb_nb; int /*<<< orphan*/  usb_phy; int /*<<< orphan*/  charger; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bq25890_chip_reset (struct bq25890_device*) ; 
 struct bq25890_device* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bq25890_remove(struct i2c_client *client)
{
	struct bq25890_device *bq = i2c_get_clientdata(client);

	power_supply_unregister(bq->charger);

	if (!IS_ERR_OR_NULL(bq->usb_phy))
		usb_unregister_notifier(bq->usb_phy, &bq->usb_nb);

	/* reset all registers to default values */
	bq25890_chip_reset(bq);

	return 0;
}
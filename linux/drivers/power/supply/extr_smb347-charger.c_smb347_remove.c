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
struct smb347_charger {int /*<<< orphan*/  mains; TYPE_1__* pdata; int /*<<< orphan*/  usb; int /*<<< orphan*/  battery; } ;
struct i2c_client {scalar_t__ irq; } ;
struct TYPE_2__ {scalar_t__ use_mains; scalar_t__ use_usb; int /*<<< orphan*/  irq_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct smb347_charger*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 struct smb347_charger* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb347_irq_disable (struct smb347_charger*) ; 

__attribute__((used)) static int smb347_remove(struct i2c_client *client)
{
	struct smb347_charger *smb = i2c_get_clientdata(client);

	if (client->irq) {
		smb347_irq_disable(smb);
		free_irq(client->irq, smb);
		gpio_free(smb->pdata->irq_gpio);
	}

	power_supply_unregister(smb->battery);
	if (smb->pdata->use_usb)
		power_supply_unregister(smb->usb);
	if (smb->pdata->use_mains)
		power_supply_unregister(smb->mains);
	return 0;
}
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
struct em28xx {int /*<<< orphan*/ * sbutton_input_dev; TYPE_1__* intf; scalar_t__ num_button_polling_addresses; int /*<<< orphan*/  buttons_query_work; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void em28xx_shutdown_buttons(struct em28xx *dev)
{
	/* Cancel polling */
	cancel_delayed_work_sync(&dev->buttons_query_work);
	/* Clear polling addresses list */
	dev->num_button_polling_addresses = 0;
	/* Deregister input devices */
	if (dev->sbutton_input_dev) {
		dev_info(&dev->intf->dev, "Deregistering snapshot button\n");
		input_unregister_device(dev->sbutton_input_dev);
		dev->sbutton_input_dev = NULL;
	}
}
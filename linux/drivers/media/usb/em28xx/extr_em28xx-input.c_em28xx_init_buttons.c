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
typedef  size_t u8 ;
struct em28xx_button {scalar_t__ role; scalar_t__ reg_r; int /*<<< orphan*/  reg_clearing; } ;
struct TYPE_3__ {struct em28xx_button* buttons; } ;
struct em28xx {size_t num_button_polling_addresses; scalar_t__* button_polling_addresses; int /*<<< orphan*/  button_polling_interval; int /*<<< orphan*/  buttons_query_work; int /*<<< orphan*/  button_polling_last_values; TYPE_2__* intf; TYPE_1__ board; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EM28XX_BUTTONS_DEBOUNCED_QUERY_INTERVAL ; 
 int /*<<< orphan*/  EM28XX_BUTTONS_VOLATILE_QUERY_INTERVAL ; 
 scalar_t__ EM28XX_BUTTON_ILLUMINATION ; 
 scalar_t__ EM28XX_BUTTON_SNAPSHOT ; 
 int /*<<< orphan*/  EM28XX_LED_ILLUMINATION ; 
 scalar_t__ EM28XX_NUM_BUTTON_ADDRESSES_MAX ; 
 scalar_t__ EM28XX_NUM_BUTTON_ROLES ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  em28xx_find_led (struct em28xx*,int /*<<< orphan*/ ) ; 
 scalar_t__ em28xx_register_snapshot_button (struct em28xx*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void em28xx_init_buttons(struct em28xx *dev)
{
	u8  i = 0, j = 0;
	bool addr_new = false;

	dev->button_polling_interval = EM28XX_BUTTONS_DEBOUNCED_QUERY_INTERVAL;
	while (dev->board.buttons[i].role >= 0 &&
	       dev->board.buttons[i].role < EM28XX_NUM_BUTTON_ROLES) {
		const struct em28xx_button *button = &dev->board.buttons[i];

		/* Check if polling address is already on the list */
		addr_new = true;
		for (j = 0; j < dev->num_button_polling_addresses; j++) {
			if (button->reg_r == dev->button_polling_addresses[j]) {
				addr_new = false;
				break;
			}
		}
		/* Check if max. number of polling addresses is exceeded */
		if (addr_new && dev->num_button_polling_addresses
					   >= EM28XX_NUM_BUTTON_ADDRESSES_MAX) {
			WARN_ONCE(1, "BUG: maximum number of button polling addresses exceeded.");
			goto next_button;
		}
		/* Button role specific checks and actions */
		if (button->role == EM28XX_BUTTON_SNAPSHOT) {
			/* Register input device */
			if (em28xx_register_snapshot_button(dev) < 0)
				goto next_button;
		} else if (button->role == EM28XX_BUTTON_ILLUMINATION) {
			/* Check sanity */
			if (!em28xx_find_led(dev, EM28XX_LED_ILLUMINATION)) {
				dev_err(&dev->intf->dev,
					"BUG: illumination button defined, but no illumination LED.\n");
				goto next_button;
			}
		}
		/* Add read address to list of polling addresses */
		if (addr_new) {
			unsigned int index = dev->num_button_polling_addresses;

			dev->button_polling_addresses[index] = button->reg_r;
			dev->num_button_polling_addresses++;
		}
		/* Reduce polling interval if necessary */
		if (!button->reg_clearing)
			dev->button_polling_interval =
					 EM28XX_BUTTONS_VOLATILE_QUERY_INTERVAL;
next_button:
		/* Next button */
		i++;
	}

	/* Start polling */
	if (dev->num_button_polling_addresses) {
		memset(dev->button_polling_last_values, 0,
		       EM28XX_NUM_BUTTON_ADDRESSES_MAX);
		schedule_delayed_work(&dev->buttons_query_work,
				      msecs_to_jiffies(dev->button_polling_interval));
	}
}
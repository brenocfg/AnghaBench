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
typedef  int u8 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 scalar_t__ gpio_direction_input (int) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 int /*<<< orphan*/  gpio_get_value (int) ; 
 scalar_t__ gpio_request (int,char*) ; 

__attribute__((used)) static int zeus_get_pcb_info(struct i2c_client *client, unsigned gpio,
			     unsigned ngpio, void *context)
{
	int i;
	u8 pcb_info = 0;

	for (i = 0; i < 8; i++) {
		int pcb_bit = gpio + i + 8;

		if (gpio_request(pcb_bit, "pcb info")) {
			dev_err(&client->dev, "Can't request pcb info %d\n", i);
			continue;
		}

		if (gpio_direction_input(pcb_bit)) {
			dev_err(&client->dev, "Can't read pcb info %d\n", i);
			gpio_free(pcb_bit);
			continue;
		}

		pcb_info |= !!gpio_get_value(pcb_bit) << i;

		gpio_free(pcb_bit);
	}

	dev_info(&client->dev, "Zeus PCB version %d issue %d\n",
		 pcb_info >> 4, pcb_info & 0xf);

	return 0;
}
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
struct dln2_gpio_pin_val {int value; int /*<<< orphan*/  pin; } ;
struct dln2_gpio {int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  DLN2_GPIO_PIN_SET_OUT_VAL ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned int) ; 
 int dln2_transfer_tx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dln2_gpio_pin_val*,int) ; 

__attribute__((used)) static int dln2_gpio_pin_set_out_val(struct dln2_gpio *dln2,
				     unsigned int pin, int value)
{
	struct dln2_gpio_pin_val req = {
		.pin = cpu_to_le16(pin),
		.value = value,
	};

	return dln2_transfer_tx(dln2->pdev, DLN2_GPIO_PIN_SET_OUT_VAL, &req,
				sizeof(req));
}
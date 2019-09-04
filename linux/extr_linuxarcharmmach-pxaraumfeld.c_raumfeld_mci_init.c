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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_W2W_PDN ; 
 int /*<<< orphan*/  GPIO_W2W_RESET ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int raumfeld_mci_init(struct device *dev, irq_handler_t isr, void *data)
{
	gpio_set_value(GPIO_W2W_RESET, 1);
	gpio_set_value(GPIO_W2W_PDN, 1);

	return 0;
}
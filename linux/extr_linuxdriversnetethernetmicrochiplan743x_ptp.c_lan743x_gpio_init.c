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
struct lan743x_gpio {int gpio_cfg0; int gpio_cfg1; int gpio_cfg2; int gpio_cfg3; int /*<<< orphan*/  gpio_lock; } ;
struct lan743x_adapter {struct lan743x_gpio gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_CFG0 ; 
 int /*<<< orphan*/  GPIO_CFG1 ; 
 int /*<<< orphan*/  GPIO_CFG2 ; 
 int /*<<< orphan*/  GPIO_CFG3 ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int lan743x_gpio_init(struct lan743x_adapter *adapter)
{
	struct lan743x_gpio *gpio = &adapter->gpio;

	spin_lock_init(&gpio->gpio_lock);

	gpio->gpio_cfg0 = 0; /* set all direction to input, data = 0 */
	gpio->gpio_cfg1 = 0x0FFF0000;/* disable all gpio, set to open drain */
	gpio->gpio_cfg2 = 0;/* set all to 1588 low polarity level */
	gpio->gpio_cfg3 = 0;/* disable all 1588 output */
	lan743x_csr_write(adapter, GPIO_CFG0, gpio->gpio_cfg0);
	lan743x_csr_write(adapter, GPIO_CFG1, gpio->gpio_cfg1);
	lan743x_csr_write(adapter, GPIO_CFG2, gpio->gpio_cfg2);
	lan743x_csr_write(adapter, GPIO_CFG3, gpio->gpio_cfg3);

	return 0;
}
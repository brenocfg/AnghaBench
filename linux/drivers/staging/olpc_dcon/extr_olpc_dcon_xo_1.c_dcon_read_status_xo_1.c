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

/* Variables and functions */
 int /*<<< orphan*/  GPIO_NEGATIVE_EDGE_STS ; 
 size_t OLPC_DCON_STAT0 ; 
 size_t OLPC_DCON_STAT1 ; 
 int /*<<< orphan*/  OLPC_GPIO_DCON_IRQ ; 
 int /*<<< orphan*/  cs5535_gpio_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gpios ; 

__attribute__((used)) static int dcon_read_status_xo_1(u8 *status)
{
	*status = gpiod_get_value(gpios[OLPC_DCON_STAT0]);
	*status |= gpiod_get_value(gpios[OLPC_DCON_STAT1]) << 1;

	/* Clear the negative edge status for GPIO7 */
	cs5535_gpio_set(OLPC_GPIO_DCON_IRQ, GPIO_NEGATIVE_EDGE_STS);

	return 0;
}
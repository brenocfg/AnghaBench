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
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MMD_PHYXS ; 
 int /*<<< orphan*/  TXC_GPIO_OUTPUT ; 
 int /*<<< orphan*/  ef4_mdio_set_flag (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void falcon_txc_set_gpio_val(struct ef4_nic *efx, int pin, int on)
{
	ef4_mdio_set_flag(efx, MDIO_MMD_PHYXS, TXC_GPIO_OUTPUT, 1 << pin, on);
}
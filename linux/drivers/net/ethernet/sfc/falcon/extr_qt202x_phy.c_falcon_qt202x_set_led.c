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
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int MDIO_QUAKE_LED0_REG ; 
 int /*<<< orphan*/  ef4_mdio_write (struct ef4_nic*,int /*<<< orphan*/ ,int,int) ; 

void falcon_qt202x_set_led(struct ef4_nic *p, int led, int mode)
{
	int addr = MDIO_QUAKE_LED0_REG + led;
	ef4_mdio_write(p, MDIO_MMD_PMAPMD, addr, mode);
}
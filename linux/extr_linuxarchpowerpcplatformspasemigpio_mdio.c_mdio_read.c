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
struct mii_bus {int dummy; } ;

/* Variables and functions */
 int MDIO_PIN (struct mii_bus*) ; 
 scalar_t__ gpio_regs ; 
 int in_le32 (scalar_t__) ; 

__attribute__((used)) static inline int mdio_read(struct mii_bus *bus)
{
	return !!(in_le32(gpio_regs+0x40) & (1 << MDIO_PIN(bus)));
}
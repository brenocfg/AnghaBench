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
struct phy_device {int dummy; } ;
struct dsa_switch {int /*<<< orphan*/  slave_mii_bus; } ;

/* Variables and functions */
#define  B53_CPU_PORT 129 
#define  B53_CPU_PORT_25 128 
 struct phy_device* mdiobus_get_phy (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct phy_device *b53_get_phy_device(struct dsa_switch *ds, int port)
{
	/* These ports typically do not have built-in PHYs */
	switch (port) {
	case B53_CPU_PORT_25:
	case 7:
	case B53_CPU_PORT:
		return NULL;
	}

	return mdiobus_get_phy(ds->slave_mii_bus, port);
}
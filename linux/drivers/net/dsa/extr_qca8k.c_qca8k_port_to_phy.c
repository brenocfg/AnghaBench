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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u32
qca8k_port_to_phy(int port)
{
	/* From Andrew Lunn:
	 * Port 0 has no internal phy.
	 * Port 1 has an internal PHY at MDIO address 0.
	 * Port 2 has an internal PHY at MDIO address 1.
	 * ...
	 * Port 5 has an internal PHY at MDIO address 4.
	 * Port 6 has no internal PHY.
	 */

	return port - 1;
}
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
typedef  int /*<<< orphan*/  u8 ;
struct ksz_device {int features; } ;

/* Variables and functions */
 int NEW_XMII ; 
 int /*<<< orphan*/  PORT_MII_1000MBIT_S1 ; 
 int /*<<< orphan*/  PORT_MII_NOT_1GBIT ; 

__attribute__((used)) static void ksz9477_set_gbit(struct ksz_device *dev, bool gbit, u8 *data)
{
	if (dev->features & NEW_XMII) {
		if (gbit)
			*data &= ~PORT_MII_NOT_1GBIT;
		else
			*data |= PORT_MII_NOT_1GBIT;
	} else {
		if (gbit)
			*data |= PORT_MII_1000MBIT_S1;
		else
			*data &= ~PORT_MII_1000MBIT_S1;
	}
}
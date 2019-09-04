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
typedef  int /*<<< orphan*/  u16 ;
struct mii_bus {struct b44* priv; } ;
struct b44 {int dummy; } ;

/* Variables and functions */
 int __b44_writephy (struct b44*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int b44_mdio_write_phylib(struct mii_bus *bus, int phy_id, int location,
				 u16 val)
{
	struct b44 *bp = bus->priv;
	return __b44_writephy(bp, phy_id, location, val);
}
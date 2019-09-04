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
struct mii_bus {struct ethoc* priv; } ;
struct ethoc {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MIIADDRESS ; 
 int /*<<< orphan*/  MIIADDRESS_ADDR (int,int) ; 
 int /*<<< orphan*/  MIICOMMAND ; 
 int /*<<< orphan*/  MIICOMMAND_READ ; 
 int /*<<< orphan*/  MIIRX_DATA ; 
 int /*<<< orphan*/  MIISTATUS ; 
 int MIISTATUS_BUSY ; 
 int ethoc_read (struct ethoc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethoc_write (struct ethoc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ethoc_mdio_read(struct mii_bus *bus, int phy, int reg)
{
	struct ethoc *priv = bus->priv;
	int i;

	ethoc_write(priv, MIIADDRESS, MIIADDRESS_ADDR(phy, reg));
	ethoc_write(priv, MIICOMMAND, MIICOMMAND_READ);

	for (i = 0; i < 5; i++) {
		u32 status = ethoc_read(priv, MIISTATUS);
		if (!(status & MIISTATUS_BUSY)) {
			u32 data = ethoc_read(priv, MIIRX_DATA);
			/* reset MII command register */
			ethoc_write(priv, MIICOMMAND, 0);
			return data;
		}
		usleep_range(100, 200);
	}

	return -EBUSY;
}
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
typedef  int u16 ;
struct mii_bus {struct dnet* priv; } ;
struct dnet {int dummy; } ;

/* Variables and functions */
 int DNET_INTERNAL_GMII_MNG_CMD_FIN ; 
 int /*<<< orphan*/  DNET_INTERNAL_GMII_MNG_CTL_REG ; 
 int /*<<< orphan*/  DNET_INTERNAL_GMII_MNG_DAT_REG ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int dnet_readw_mac (struct dnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dnet_writew_mac (struct dnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int) ; 

__attribute__((used)) static int dnet_mdio_read(struct mii_bus *bus, int mii_id, int regnum)
{
	struct dnet *bp = bus->priv;
	u16 value;

	while (!(dnet_readw_mac(bp, DNET_INTERNAL_GMII_MNG_CTL_REG)
				& DNET_INTERNAL_GMII_MNG_CMD_FIN))
		cpu_relax();

	/* only 5 bits allowed for phy-addr and reg_offset */
	mii_id &= 0x1f;
	regnum &= 0x1f;

	/* prepare reg_value for a read */
	value = (mii_id << 8);
	value |= regnum;

	/* write control word */
	dnet_writew_mac(bp, DNET_INTERNAL_GMII_MNG_CTL_REG, value);

	/* wait for end of transfer */
	while (!(dnet_readw_mac(bp, DNET_INTERNAL_GMII_MNG_CTL_REG)
				& DNET_INTERNAL_GMII_MNG_CMD_FIN))
		cpu_relax();

	value = dnet_readw_mac(bp, DNET_INTERNAL_GMII_MNG_DAT_REG);

	pr_debug("mdio_read %02x:%02x <- %04x\n", mii_id, regnum, value);

	return value;
}
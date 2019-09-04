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
struct b44 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B44_EMAC_ISTAT ; 
 int /*<<< orphan*/  B44_MDIO_DATA ; 
 int EMAC_INT_MII ; 
 int MDIO_DATA_DATA ; 
 int MDIO_DATA_OP_SHIFT ; 
 int MDIO_DATA_PMD_SHIFT ; 
 int MDIO_DATA_RA_SHIFT ; 
 int MDIO_DATA_SB_START ; 
 int MDIO_DATA_TA_SHIFT ; 
 int MDIO_OP_READ ; 
 int MDIO_TA_VALID ; 
 int b44_wait_bit (struct b44*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int br32 (struct b44*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bw32 (struct b44*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __b44_readphy(struct b44 *bp, int phy_addr, int reg, u32 *val)
{
	int err;

	bw32(bp, B44_EMAC_ISTAT, EMAC_INT_MII);
	bw32(bp, B44_MDIO_DATA, (MDIO_DATA_SB_START |
			     (MDIO_OP_READ << MDIO_DATA_OP_SHIFT) |
			     (phy_addr << MDIO_DATA_PMD_SHIFT) |
			     (reg << MDIO_DATA_RA_SHIFT) |
			     (MDIO_TA_VALID << MDIO_DATA_TA_SHIFT)));
	err = b44_wait_bit(bp, B44_EMAC_ISTAT, EMAC_INT_MII, 100, 0);
	*val = br32(bp, B44_MDIO_DATA) & MDIO_DATA_DATA;

	return err;
}
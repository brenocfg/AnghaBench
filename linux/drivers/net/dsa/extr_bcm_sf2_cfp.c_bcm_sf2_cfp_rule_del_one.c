#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  unique; int /*<<< orphan*/  used; } ;
struct bcm_sf2_priv {TYPE_1__ cfp; } ;

/* Variables and functions */
 int CHAIN_ID_MASK ; 
 int /*<<< orphan*/  CORE_CFP_DATA_PORT (int) ; 
 int OP_SEL_READ ; 
 int OP_SEL_WRITE ; 
 int SLICE_VALID ; 
 int TCAM_SEL ; 
 int bcm_sf2_cfp_op (struct bcm_sf2_priv*,int) ; 
 int /*<<< orphan*/  bcm_sf2_cfp_rule_addr_set (struct bcm_sf2_priv*,int) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int core_readl (struct bcm_sf2_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_writel (struct bcm_sf2_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm_sf2_cfp_rule_del_one(struct bcm_sf2_priv *priv, int port,
				    u32 loc, u32 *next_loc)
{
	int ret;
	u32 reg;

	/* Indicate which rule we want to read */
	bcm_sf2_cfp_rule_addr_set(priv, loc);

	ret =  bcm_sf2_cfp_op(priv, OP_SEL_READ | TCAM_SEL);
	if (ret)
		return ret;

	/* Check if this is possibly an IPv6 rule that would
	 * indicate we need to delete its companion rule
	 * as well
	 */
	reg = core_readl(priv, CORE_CFP_DATA_PORT(6));
	if (next_loc)
		*next_loc = (reg >> 24) & CHAIN_ID_MASK;

	/* Clear its valid bits */
	reg = core_readl(priv, CORE_CFP_DATA_PORT(0));
	reg &= ~SLICE_VALID;
	core_writel(priv, reg, CORE_CFP_DATA_PORT(0));

	/* Write back this entry into the TCAM now */
	ret = bcm_sf2_cfp_op(priv, OP_SEL_WRITE | TCAM_SEL);
	if (ret)
		return ret;

	clear_bit(loc, priv->cfp.used);
	clear_bit(loc, priv->cfp.unique);

	return 0;
}
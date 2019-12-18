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
typedef  unsigned int u32 ;
struct bcm_sf2_priv {int dummy; } ;

/* Variables and functions */
 int ACT_POL_RAM ; 
 unsigned int BIT (scalar_t__) ; 
 unsigned int CHAIN_ID_SHIFT ; 
 unsigned int CHANGE_FWRD_MAP_IB_REP_ARL ; 
 unsigned int CHANGE_TC ; 
 int /*<<< orphan*/  CORE_ACT_POL_DATA0 ; 
 int /*<<< orphan*/  CORE_ACT_POL_DATA1 ; 
 int /*<<< orphan*/  CORE_ACT_POL_DATA2 ; 
 int /*<<< orphan*/  CORE_RATE_METER0 ; 
 scalar_t__ DST_MAP_IB_SHIFT ; 
 unsigned int LOOP_BK_EN ; 
 unsigned int NEW_TC_SHIFT ; 
 int OP_SEL_WRITE ; 
 unsigned int POLICER_MODE_DISABLE ; 
 int RATE_METER_RAM ; 
 int bcm_sf2_cfp_op (struct bcm_sf2_priv*,int) ; 
 int /*<<< orphan*/  core_writel (struct bcm_sf2_priv*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 

__attribute__((used)) static int bcm_sf2_cfp_act_pol_set(struct bcm_sf2_priv *priv,
				   unsigned int rule_index,
				   int src_port,
				   unsigned int port_num,
				   unsigned int queue_num,
				   bool fwd_map_change)
{
	int ret;
	u32 reg;

	/* Replace ARL derived destination with DST_MAP derived, define
	 * which port and queue this should be forwarded to.
	 */
	if (fwd_map_change)
		reg = CHANGE_FWRD_MAP_IB_REP_ARL |
		      BIT(port_num + DST_MAP_IB_SHIFT) |
		      CHANGE_TC | queue_num << NEW_TC_SHIFT;
	else
		reg = 0;

	/* Enable looping back to the original port */
	if (src_port == port_num)
		reg |= LOOP_BK_EN;

	core_writel(priv, reg, CORE_ACT_POL_DATA0);

	/* Set classification ID that needs to be put in Broadcom tag */
	core_writel(priv, rule_index << CHAIN_ID_SHIFT, CORE_ACT_POL_DATA1);

	core_writel(priv, 0, CORE_ACT_POL_DATA2);

	/* Configure policer RAM now */
	ret = bcm_sf2_cfp_op(priv, OP_SEL_WRITE | ACT_POL_RAM);
	if (ret) {
		pr_err("Policer entry at %d failed\n", rule_index);
		return ret;
	}

	/* Disable the policer */
	core_writel(priv, POLICER_MODE_DISABLE, CORE_RATE_METER0);

	/* Now the rate meter */
	ret = bcm_sf2_cfp_op(priv, OP_SEL_WRITE | RATE_METER_RAM);
	if (ret) {
		pr_err("Meter entry at %d failed\n", rule_index);
		return ret;
	}

	return 0;
}
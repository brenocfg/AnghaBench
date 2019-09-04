#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int ring_cookie; int /*<<< orphan*/  location; } ;
struct ethtool_rxnfc {int /*<<< orphan*/  data; TYPE_1__ fs; } ;
struct bcm_sf2_priv {int dummy; } ;

/* Variables and functions */
 int ACT_POL_RAM ; 
 int /*<<< orphan*/  CORE_ACT_POL_DATA0 ; 
 int /*<<< orphan*/  CORE_CFP_DATA_PORT (int) ; 
 int DST_MAP_IB_MASK ; 
 int DST_MAP_IB_SHIFT ; 
 int EINVAL ; 
 int L3_FRAMING_SHIFT ; 
 int NEW_TC_MASK ; 
 int NEW_TC_SHIFT ; 
 int OP_SEL_READ ; 
 int SF2_NUM_EGRESS_QUEUES ; 
 int TCAM_SEL ; 
 int bcm_sf2_cfp_ipv4_rule_get (struct bcm_sf2_priv*,int,TYPE_1__*) ; 
 int bcm_sf2_cfp_ipv6_rule_get (struct bcm_sf2_priv*,int,TYPE_1__*,int) ; 
 int bcm_sf2_cfp_op (struct bcm_sf2_priv*,int) ; 
 int /*<<< orphan*/  bcm_sf2_cfp_rule_addr_set (struct bcm_sf2_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_sf2_cfp_rule_size (struct bcm_sf2_priv*) ; 
 int /*<<< orphan*/  bcm_sf2_invert_masks (TYPE_1__*) ; 
 int core_readl (struct bcm_sf2_priv*,int /*<<< orphan*/ ) ; 
 int fls (int) ; 

__attribute__((used)) static int bcm_sf2_cfp_rule_get(struct bcm_sf2_priv *priv, int port,
				struct ethtool_rxnfc *nfc)
{
	u32 reg, ipv4_or_chain_id;
	unsigned int queue_num;
	int ret;

	bcm_sf2_cfp_rule_addr_set(priv, nfc->fs.location);

	ret = bcm_sf2_cfp_op(priv, OP_SEL_READ | ACT_POL_RAM);
	if (ret)
		return ret;

	reg = core_readl(priv, CORE_ACT_POL_DATA0);

	ret = bcm_sf2_cfp_op(priv, OP_SEL_READ | TCAM_SEL);
	if (ret)
		return ret;

	/* Extract the destination port */
	nfc->fs.ring_cookie = fls((reg >> DST_MAP_IB_SHIFT) &
				  DST_MAP_IB_MASK) - 1;

	/* There is no Port 6, so we compensate for that here */
	if (nfc->fs.ring_cookie >= 6)
		nfc->fs.ring_cookie++;
	nfc->fs.ring_cookie *= SF2_NUM_EGRESS_QUEUES;

	/* Extract the destination queue */
	queue_num = (reg >> NEW_TC_SHIFT) & NEW_TC_MASK;
	nfc->fs.ring_cookie += queue_num;

	/* Extract the L3_FRAMING or CHAIN_ID */
	reg = core_readl(priv, CORE_CFP_DATA_PORT(6));

	/* With IPv6 rules this would contain a non-zero chain ID since
	 * we reserve entry 0 and it cannot be used. So if we read 0 here
	 * this means an IPv4 rule.
	 */
	ipv4_or_chain_id = (reg >> L3_FRAMING_SHIFT) & 0xff;
	if (ipv4_or_chain_id == 0)
		ret = bcm_sf2_cfp_ipv4_rule_get(priv, port, &nfc->fs);
	else
		ret = bcm_sf2_cfp_ipv6_rule_get(priv, port, &nfc->fs,
						ipv4_or_chain_id);
	if (ret)
		return ret;

	/* Read last to avoid next entry clobbering the results during search
	 * operations
	 */
	reg = core_readl(priv, CORE_CFP_DATA_PORT(7));
	if (!(reg & 1 << port))
		return -EINVAL;

	bcm_sf2_invert_masks(&nfc->fs);

	/* Put the TCAM size here */
	nfc->data = bcm_sf2_cfp_rule_size(priv);

	return 0;
}
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
struct nps_enet_priv {int ge_mac_cfg_2_value; int ge_mac_cfg_3_value; } ;
struct net_device {int mtu; } ;
typedef  int s32 ;

/* Variables and functions */
 int CFG_0_RX_CRC_STRIP_SHIFT ; 
 int CFG_0_RX_EN_SHIFT ; 
 int CFG_0_RX_FC_EN_SHIFT ; 
 int CFG_0_RX_IFG_SHIFT ; 
 int CFG_0_RX_PR_CHECK_EN_SHIFT ; 
 int CFG_0_TX_CRC_EN_SHIFT ; 
 int CFG_0_TX_EN_SHIFT ; 
 int CFG_0_TX_FC_EN_SHIFT ; 
 int CFG_0_TX_FC_RETR_SHIFT ; 
 int CFG_0_TX_IFG_SHIFT ; 
 int CFG_0_TX_PAD_EN_SHIFT ; 
 int CFG_0_TX_PR_LEN_SHIFT ; 
 int CFG_2_DISK_DA_MASK ; 
 int CFG_2_DISK_DA_SHIFT ; 
 int CFG_2_DISK_MC_MASK ; 
 int CFG_2_DISK_MC_SHIFT ; 
 int CFG_2_STAT_EN_MASK ; 
 int CFG_2_STAT_EN_SHIFT ; 
 int CFG_3_CF_DROP_MASK ; 
 int CFG_3_CF_DROP_SHIFT ; 
 int CFG_3_MAX_LEN_MASK ; 
 int CFG_3_MAX_LEN_SHIFT ; 
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 int NPS_ENET_ENABLE ; 
 int NPS_ENET_GE_MAC_CFG_0_RX_IFG ; 
 int NPS_ENET_GE_MAC_CFG_0_TX_FC_RETR ; 
 int NPS_ENET_GE_MAC_CFG_0_TX_IFG ; 
 int NPS_ENET_GE_MAC_CFG_0_TX_PR_LEN ; 
 int NPS_ENET_GE_MAC_CFG_2_STAT_EN ; 
 int NPS_ENET_MAX_FRAME_LENGTH ; 
 int /*<<< orphan*/  NPS_ENET_REG_BUF_INT_ENABLE ; 
 int /*<<< orphan*/  NPS_ENET_REG_GE_MAC_CFG_0 ; 
 int /*<<< orphan*/  NPS_ENET_REG_GE_MAC_CFG_2 ; 
 int /*<<< orphan*/  NPS_ENET_REG_GE_MAC_CFG_3 ; 
 int RX_RDY_SHIFT ; 
 int TX_DONE_SHIFT ; 
 struct nps_enet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nps_enet_reg_set (struct nps_enet_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nps_enet_set_hw_mac_address (struct net_device*) ; 

__attribute__((used)) static void nps_enet_hw_enable_control(struct net_device *ndev)
{
	struct nps_enet_priv *priv = netdev_priv(ndev);
	u32 ge_mac_cfg_0_value = 0, buf_int_enable_value = 0;
	u32 *ge_mac_cfg_2_value = &priv->ge_mac_cfg_2_value;
	u32 *ge_mac_cfg_3_value = &priv->ge_mac_cfg_3_value;
	s32 max_frame_length;

	/* Enable Rx and Tx statistics */
	*ge_mac_cfg_2_value = (*ge_mac_cfg_2_value & ~CFG_2_STAT_EN_MASK)
		 | NPS_ENET_GE_MAC_CFG_2_STAT_EN << CFG_2_STAT_EN_SHIFT;

	/* Discard packets with different MAC address */
	*ge_mac_cfg_2_value = (*ge_mac_cfg_2_value & ~CFG_2_DISK_DA_MASK)
		 | NPS_ENET_ENABLE << CFG_2_DISK_DA_SHIFT;

	/* Discard multicast packets */
	*ge_mac_cfg_2_value = (*ge_mac_cfg_2_value & ~CFG_2_DISK_MC_MASK)
		 | NPS_ENET_ENABLE << CFG_2_DISK_MC_SHIFT;

	nps_enet_reg_set(priv, NPS_ENET_REG_GE_MAC_CFG_2,
			 *ge_mac_cfg_2_value);

	/* Discard Packets bigger than max frame length */
	max_frame_length = ETH_HLEN + ndev->mtu + ETH_FCS_LEN;
	if (max_frame_length <= NPS_ENET_MAX_FRAME_LENGTH) {
		*ge_mac_cfg_3_value =
			 (*ge_mac_cfg_3_value & ~CFG_3_MAX_LEN_MASK)
			 | max_frame_length << CFG_3_MAX_LEN_SHIFT;
	}

	/* Enable interrupts */
	buf_int_enable_value |= NPS_ENET_ENABLE << RX_RDY_SHIFT;
	buf_int_enable_value |= NPS_ENET_ENABLE << TX_DONE_SHIFT;
	nps_enet_reg_set(priv, NPS_ENET_REG_BUF_INT_ENABLE,
			 buf_int_enable_value);

	/* Write device MAC address to HW */
	nps_enet_set_hw_mac_address(ndev);

	/* Rx and Tx HW features */
	ge_mac_cfg_0_value |= NPS_ENET_ENABLE << CFG_0_TX_PAD_EN_SHIFT;
	ge_mac_cfg_0_value |= NPS_ENET_ENABLE << CFG_0_TX_CRC_EN_SHIFT;
	ge_mac_cfg_0_value |= NPS_ENET_ENABLE << CFG_0_RX_CRC_STRIP_SHIFT;

	/* IFG configuration */
	ge_mac_cfg_0_value |=
		 NPS_ENET_GE_MAC_CFG_0_RX_IFG << CFG_0_RX_IFG_SHIFT;
	ge_mac_cfg_0_value |=
		 NPS_ENET_GE_MAC_CFG_0_TX_IFG << CFG_0_TX_IFG_SHIFT;

	/* preamble configuration */
	ge_mac_cfg_0_value |= NPS_ENET_ENABLE << CFG_0_RX_PR_CHECK_EN_SHIFT;
	ge_mac_cfg_0_value |=
		 NPS_ENET_GE_MAC_CFG_0_TX_PR_LEN << CFG_0_TX_PR_LEN_SHIFT;

	/* enable flow control frames */
	ge_mac_cfg_0_value |= NPS_ENET_ENABLE << CFG_0_TX_FC_EN_SHIFT;
	ge_mac_cfg_0_value |= NPS_ENET_ENABLE << CFG_0_RX_FC_EN_SHIFT;
	ge_mac_cfg_0_value |=
		 NPS_ENET_GE_MAC_CFG_0_TX_FC_RETR << CFG_0_TX_FC_RETR_SHIFT;
	*ge_mac_cfg_3_value = (*ge_mac_cfg_3_value & ~CFG_3_CF_DROP_MASK)
		 | NPS_ENET_ENABLE << CFG_3_CF_DROP_SHIFT;

	/* Enable Rx and Tx */
	ge_mac_cfg_0_value |= NPS_ENET_ENABLE << CFG_0_RX_EN_SHIFT;
	ge_mac_cfg_0_value |= NPS_ENET_ENABLE << CFG_0_TX_EN_SHIFT;

	nps_enet_reg_set(priv, NPS_ENET_REG_GE_MAC_CFG_3,
			 *ge_mac_cfg_3_value);
	nps_enet_reg_set(priv, NPS_ENET_REG_GE_MAC_CFG_0,
			 ge_mac_cfg_0_value);
}
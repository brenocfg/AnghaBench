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
struct aq_nic_cfg_s {scalar_t__ is_rss; } ;
struct aq_hw_s {struct aq_nic_cfg_s* aq_nic_cfg; } ;

/* Variables and functions */
 int HW_ATL_B0_MAC_MAX ; 
 scalar_t__ IS_CHIP_FEATURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPF2 ; 
 int aq_hw_err_from_flags (struct aq_hw_s*) ; 
 int /*<<< orphan*/  aq_hw_write_reg (struct aq_hw_s*,int,int) ; 
 int /*<<< orphan*/  hw_atl_rdm_rx_dca_en_set (struct aq_hw_s*,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_rdm_rx_dca_mode_set (struct aq_hw_s*,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_rdm_rx_desc_wr_wb_irq_en_set (struct aq_hw_s*,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_reg_rx_flr_mcst_flr_msk_set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  hw_atl_reg_rx_flr_mcst_flr_set (struct aq_hw_s*,int,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_reg_rx_flr_rss_control1set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  hw_atl_rpb_rpf_rx_traf_class_mode_set (struct aq_hw_s*,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_rpb_rx_flow_ctl_mode_set (struct aq_hw_s*,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_rpf_vlan_accept_untagged_packets_set (struct aq_hw_s*,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_rpf_vlan_inner_etht_set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  hw_atl_rpf_vlan_outer_etht_set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  hw_atl_rpf_vlan_prom_mode_en_set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  hw_atl_rpf_vlan_untagged_act_set (struct aq_hw_s*,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_rpfl2_uc_flr_en_set (struct aq_hw_s*,unsigned int,int) ; 
 int /*<<< orphan*/  hw_atl_rpfl2broadcast_count_threshold_set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  hw_atl_rpfl2broadcast_flr_act_set (struct aq_hw_s*,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_rpfl2unicast_flr_act_set (struct aq_hw_s*,unsigned int,int) ; 

__attribute__((used)) static int hw_atl_b0_hw_init_rx_path(struct aq_hw_s *self)
{
	struct aq_nic_cfg_s *cfg = self->aq_nic_cfg;
	int i;

	/* Rx TC/RSS number config */
	hw_atl_rpb_rpf_rx_traf_class_mode_set(self, 1U);

	/* Rx flow control */
	hw_atl_rpb_rx_flow_ctl_mode_set(self, 1U);

	/* RSS Ring selection */
	hw_atl_reg_rx_flr_rss_control1set(self, cfg->is_rss ?
					0xB3333333U : 0x00000000U);

	/* Multicast filters */
	for (i = HW_ATL_B0_MAC_MAX; i--;) {
		hw_atl_rpfl2_uc_flr_en_set(self, (i == 0U) ? 1U : 0U, i);
		hw_atl_rpfl2unicast_flr_act_set(self, 1U, i);
	}

	hw_atl_reg_rx_flr_mcst_flr_msk_set(self, 0x00000000U);
	hw_atl_reg_rx_flr_mcst_flr_set(self, 0x00010FFFU, 0U);

	/* Vlan filters */
	hw_atl_rpf_vlan_outer_etht_set(self, 0x88A8U);
	hw_atl_rpf_vlan_inner_etht_set(self, 0x8100U);

	hw_atl_rpf_vlan_prom_mode_en_set(self, 1);

	// Always accept untagged packets
	hw_atl_rpf_vlan_accept_untagged_packets_set(self, 1U);
	hw_atl_rpf_vlan_untagged_act_set(self, 1U);

	/* Rx Interrupts */
	hw_atl_rdm_rx_desc_wr_wb_irq_en_set(self, 1U);

	/* misc */
	aq_hw_write_reg(self, 0x00005040U,
			IS_CHIP_FEATURE(RPF2) ? 0x000F0000U : 0x00000000U);

	hw_atl_rpfl2broadcast_flr_act_set(self, 1U);
	hw_atl_rpfl2broadcast_count_threshold_set(self, 0xFFFFU & (~0U / 256U));

	hw_atl_rdm_rx_dca_en_set(self, 0U);
	hw_atl_rdm_rx_dca_mode_set(self, 0U);

	return aq_hw_err_from_flags(self);
}
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
struct aq_nic_cfg_s {scalar_t__ is_lro; } ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 unsigned int HW_ATL_B0_LRO_RXD_MAX ; 
 unsigned int HW_ATL_B0_RINGS_MAX ; 
 int aq_hw_err_from_flags (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_rpo_ipv4header_crc_offload_en_set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  hw_atl_rpo_lro_en_set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  hw_atl_rpo_lro_inactive_interval_set (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_rpo_lro_max_coalescing_interval_set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  hw_atl_rpo_lro_max_num_of_descriptors_set (struct aq_hw_s*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_rpo_lro_min_pay_of_first_pkt_set (struct aq_hw_s*,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_rpo_lro_patch_optimization_en_set (struct aq_hw_s*,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_rpo_lro_pkt_lim_set (struct aq_hw_s*,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_rpo_lro_qsessions_lim_set (struct aq_hw_s*,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_rpo_lro_time_base_divider_set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  hw_atl_rpo_lro_total_desc_lim_set (struct aq_hw_s*,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_rpo_tcp_udp_crc_offload_en_set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  hw_atl_tdm_large_send_offload_en_set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  hw_atl_tpo_ipv4header_crc_offload_en_set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  hw_atl_tpo_tcp_udp_crc_offload_en_set (struct aq_hw_s*,int) ; 

__attribute__((used)) static int hw_atl_b0_hw_offload_set(struct aq_hw_s *self,
				    struct aq_nic_cfg_s *aq_nic_cfg)
{
	unsigned int i;

	/* TX checksums offloads*/
	hw_atl_tpo_ipv4header_crc_offload_en_set(self, 1);
	hw_atl_tpo_tcp_udp_crc_offload_en_set(self, 1);

	/* RX checksums offloads*/
	hw_atl_rpo_ipv4header_crc_offload_en_set(self, 1);
	hw_atl_rpo_tcp_udp_crc_offload_en_set(self, 1);

	/* LSO offloads*/
	hw_atl_tdm_large_send_offload_en_set(self, 0xFFFFFFFFU);

/* LRO offloads */
	{
		unsigned int val = (8U < HW_ATL_B0_LRO_RXD_MAX) ? 0x3U :
			((4U < HW_ATL_B0_LRO_RXD_MAX) ? 0x2U :
			((2U < HW_ATL_B0_LRO_RXD_MAX) ? 0x1U : 0x0));

		for (i = 0; i < HW_ATL_B0_RINGS_MAX; i++)
			hw_atl_rpo_lro_max_num_of_descriptors_set(self, val, i);

		hw_atl_rpo_lro_time_base_divider_set(self, 0x61AU);
		hw_atl_rpo_lro_inactive_interval_set(self, 0);
		hw_atl_rpo_lro_max_coalescing_interval_set(self, 2);

		hw_atl_rpo_lro_qsessions_lim_set(self, 1U);

		hw_atl_rpo_lro_total_desc_lim_set(self, 2U);

		hw_atl_rpo_lro_patch_optimization_en_set(self, 0U);

		hw_atl_rpo_lro_min_pay_of_first_pkt_set(self, 10U);

		hw_atl_rpo_lro_pkt_lim_set(self, 1U);

		hw_atl_rpo_lro_en_set(self,
				      aq_nic_cfg->is_lro ? 0xFFFFFFFFU : 0U);
	}
	return aq_hw_err_from_flags(self);
}
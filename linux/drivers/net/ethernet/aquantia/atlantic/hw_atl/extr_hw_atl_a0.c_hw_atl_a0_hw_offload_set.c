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
struct aq_nic_cfg_s {int dummy; } ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int aq_hw_err_from_flags (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_rpo_ipv4header_crc_offload_en_set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  hw_atl_rpo_tcp_udp_crc_offload_en_set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  hw_atl_tdm_large_send_offload_en_set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  hw_atl_tpo_ipv4header_crc_offload_en_set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  hw_atl_tpo_tcp_udp_crc_offload_en_set (struct aq_hw_s*,int) ; 

__attribute__((used)) static int hw_atl_a0_hw_offload_set(struct aq_hw_s *self,
				    struct aq_nic_cfg_s *aq_nic_cfg)
{
	/* TX checksums offloads*/
	hw_atl_tpo_ipv4header_crc_offload_en_set(self, 1);
	hw_atl_tpo_tcp_udp_crc_offload_en_set(self, 1);

	/* RX checksums offloads*/
	hw_atl_rpo_ipv4header_crc_offload_en_set(self, 1);
	hw_atl_rpo_tcp_udp_crc_offload_en_set(self, 1);

	/* LSO offloads*/
	hw_atl_tdm_large_send_offload_en_set(self, 0xFFFFFFFFU);

	return aq_hw_err_from_flags(self);
}
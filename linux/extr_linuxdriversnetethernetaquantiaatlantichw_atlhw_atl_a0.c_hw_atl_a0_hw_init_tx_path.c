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
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_CHIP_FEATURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPO2 ; 
 int aq_hw_err_from_flags (struct aq_hw_s*) ; 
 int /*<<< orphan*/  aq_hw_write_reg (struct aq_hw_s*,int,int) ; 
 int /*<<< orphan*/  hw_atl_tdm_tx_dca_en_set (struct aq_hw_s*,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_tdm_tx_dca_mode_set (struct aq_hw_s*,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_tdm_tx_desc_wr_wb_irq_en_set (struct aq_hw_s*,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_thm_lso_tcp_flag_of_first_pkt_set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  hw_atl_thm_lso_tcp_flag_of_last_pkt_set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  hw_atl_thm_lso_tcp_flag_of_middle_pkt_set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  hw_atl_tpb_tx_path_scp_ins_en_set (struct aq_hw_s*,unsigned int) ; 

__attribute__((used)) static int hw_atl_a0_hw_init_tx_path(struct aq_hw_s *self)
{
	hw_atl_thm_lso_tcp_flag_of_first_pkt_set(self, 0x0FF6U);
	hw_atl_thm_lso_tcp_flag_of_middle_pkt_set(self, 0x0FF6U);
	hw_atl_thm_lso_tcp_flag_of_last_pkt_set(self, 0x0F7FU);

	/* Tx interrupts */
	hw_atl_tdm_tx_desc_wr_wb_irq_en_set(self, 1U);

	/* misc */
	aq_hw_write_reg(self, 0x00007040U, IS_CHIP_FEATURE(TPO2) ?
			0x00010000U : 0x00000000U);
	hw_atl_tdm_tx_dca_en_set(self, 0U);
	hw_atl_tdm_tx_dca_mode_set(self, 0U);

	hw_atl_tpb_tx_path_scp_ins_en_set(self, 1U);

	return aq_hw_err_from_flags(self);
}
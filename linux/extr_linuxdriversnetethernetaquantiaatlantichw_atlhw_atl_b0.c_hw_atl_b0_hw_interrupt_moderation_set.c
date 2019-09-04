#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  mbps; } ;
struct aq_hw_s {TYPE_2__* aq_nic_cfg; TYPE_1__ aq_link_status; } ;
struct TYPE_4__ {int itr; int tx_itr; int rx_itr; } ;

/* Variables and functions */
#define  AQ_CFG_INTERRUPT_MODERATION_AUTO 130 
#define  AQ_CFG_INTERRUPT_MODERATION_OFF 129 
#define  AQ_CFG_INTERRUPT_MODERATION_ON 128 
 unsigned int HW_ATL_B0_RINGS_MAX ; 
 int /*<<< orphan*/  HW_ATL_INTR_MODER_MAX ; 
 int /*<<< orphan*/  HW_ATL_INTR_MODER_MIN ; 
 int aq_hw_err_from_flags (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_rdm_rdm_intr_moder_en_set (struct aq_hw_s*,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_rdm_rx_desc_wr_wb_irq_en_set (struct aq_hw_s*,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_reg_rx_intr_moder_ctrl_set (struct aq_hw_s*,int,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_reg_tx_intr_moder_ctrl_set (struct aq_hw_s*,int,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_tdm_tdm_intr_moder_en_set (struct aq_hw_s*,unsigned int) ; 
 int /*<<< orphan*/  hw_atl_tdm_tx_desc_wr_wb_irq_en_set (struct aq_hw_s*,unsigned int) ; 
 unsigned int hw_atl_utils_mbps_2_speed_index (int /*<<< orphan*/ ) ; 
 int min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hw_atl_b0_hw_interrupt_moderation_set(struct aq_hw_s *self)
{
	unsigned int i = 0U;
	u32 itr_tx = 2U;
	u32 itr_rx = 2U;

	switch (self->aq_nic_cfg->itr) {
	case  AQ_CFG_INTERRUPT_MODERATION_ON:
	case  AQ_CFG_INTERRUPT_MODERATION_AUTO:
		hw_atl_tdm_tx_desc_wr_wb_irq_en_set(self, 0U);
		hw_atl_tdm_tdm_intr_moder_en_set(self, 1U);
		hw_atl_rdm_rx_desc_wr_wb_irq_en_set(self, 0U);
		hw_atl_rdm_rdm_intr_moder_en_set(self, 1U);

		if (self->aq_nic_cfg->itr == AQ_CFG_INTERRUPT_MODERATION_ON) {
			/* HW timers are in 2us units */
			int tx_max_timer = self->aq_nic_cfg->tx_itr / 2;
			int tx_min_timer = tx_max_timer / 2;

			int rx_max_timer = self->aq_nic_cfg->rx_itr / 2;
			int rx_min_timer = rx_max_timer / 2;

			tx_max_timer = min(HW_ATL_INTR_MODER_MAX, tx_max_timer);
			tx_min_timer = min(HW_ATL_INTR_MODER_MIN, tx_min_timer);
			rx_max_timer = min(HW_ATL_INTR_MODER_MAX, rx_max_timer);
			rx_min_timer = min(HW_ATL_INTR_MODER_MIN, rx_min_timer);

			itr_tx |= tx_min_timer << 0x8U;
			itr_tx |= tx_max_timer << 0x10U;
			itr_rx |= rx_min_timer << 0x8U;
			itr_rx |= rx_max_timer << 0x10U;
		} else {
			static unsigned int hw_atl_b0_timers_table_tx_[][2] = {
				{0xfU, 0xffU}, /* 10Gbit */
				{0xfU, 0x1ffU}, /* 5Gbit */
				{0xfU, 0x1ffU}, /* 5Gbit 5GS */
				{0xfU, 0x1ffU}, /* 2.5Gbit */
				{0xfU, 0x1ffU}, /* 1Gbit */
				{0xfU, 0x1ffU}, /* 100Mbit */
			};

			static unsigned int hw_atl_b0_timers_table_rx_[][2] = {
				{0x6U, 0x38U},/* 10Gbit */
				{0xCU, 0x70U},/* 5Gbit */
				{0xCU, 0x70U},/* 5Gbit 5GS */
				{0x18U, 0xE0U},/* 2.5Gbit */
				{0x30U, 0x80U},/* 1Gbit */
				{0x4U, 0x50U},/* 100Mbit */
			};

			unsigned int speed_index =
					hw_atl_utils_mbps_2_speed_index(
						self->aq_link_status.mbps);

			/* Update user visible ITR settings */
			self->aq_nic_cfg->tx_itr = hw_atl_b0_timers_table_tx_
							[speed_index][1] * 2;
			self->aq_nic_cfg->rx_itr = hw_atl_b0_timers_table_rx_
							[speed_index][1] * 2;

			itr_tx |= hw_atl_b0_timers_table_tx_
						[speed_index][0] << 0x8U;
			itr_tx |= hw_atl_b0_timers_table_tx_
						[speed_index][1] << 0x10U;

			itr_rx |= hw_atl_b0_timers_table_rx_
						[speed_index][0] << 0x8U;
			itr_rx |= hw_atl_b0_timers_table_rx_
						[speed_index][1] << 0x10U;
		}
		break;
	case AQ_CFG_INTERRUPT_MODERATION_OFF:
		hw_atl_tdm_tx_desc_wr_wb_irq_en_set(self, 1U);
		hw_atl_tdm_tdm_intr_moder_en_set(self, 0U);
		hw_atl_rdm_rx_desc_wr_wb_irq_en_set(self, 1U);
		hw_atl_rdm_rdm_intr_moder_en_set(self, 0U);
		itr_tx = 0U;
		itr_rx = 0U;
		break;
	}

	for (i = HW_ATL_B0_RINGS_MAX; i--;) {
		hw_atl_reg_tx_intr_moder_ctrl_set(self, itr_tx, i);
		hw_atl_reg_rx_intr_moder_ctrl_set(self, itr_rx, i);
	}

	return aq_hw_err_from_flags(self);
}
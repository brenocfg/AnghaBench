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
struct tegra_cec {scalar_t__ tx_buf_cur; scalar_t__ tx_buf_cnt; scalar_t__ rx_buf_cnt; } ;
struct cec_adapter {struct tegra_cec* priv; } ;

/* Variables and functions */
 int TEGRA_CEC_HWCTRL_TX_RX_MODE ; 
 int /*<<< orphan*/  TEGRA_CEC_HW_CONTROL ; 
 int /*<<< orphan*/  TEGRA_CEC_INPUT_FILTER ; 
 int /*<<< orphan*/  TEGRA_CEC_INT_MASK ; 
 int TEGRA_CEC_INT_MASK_RX_REGISTER_FULL ; 
 int TEGRA_CEC_INT_MASK_RX_START_BIT_DETECTED ; 
 int TEGRA_CEC_INT_MASK_TX_ARBITRATION_FAILED ; 
 int TEGRA_CEC_INT_MASK_TX_BUS_ANOMALY_DETECTED ; 
 int TEGRA_CEC_INT_MASK_TX_FRAME_OR_BLOCK_NAKD ; 
 int TEGRA_CEC_INT_MASK_TX_FRAME_TRANSMITTED ; 
 int TEGRA_CEC_INT_MASK_TX_REGISTER_UNDERRUN ; 
 int /*<<< orphan*/  TEGRA_CEC_INT_STAT ; 
 int TEGRA_CEC_RX_TIM0_START_BIT_MAX_DURATION_SHIFT ; 
 int TEGRA_CEC_RX_TIM0_START_BIT_MAX_LO_TIME_SHIFT ; 
 int TEGRA_CEC_RX_TIM0_START_BIT_MIN_DURATION_SHIFT ; 
 int TEGRA_CEC_RX_TIM0_START_BIT_MIN_LO_TIME_SHIFT ; 
 int TEGRA_CEC_RX_TIM1_DATA_BIT_MAX_DURATION_SHIFT ; 
 int TEGRA_CEC_RX_TIM1_DATA_BIT_MAX_LO_TIME_SHIFT ; 
 int TEGRA_CEC_RX_TIM1_DATA_BIT_MIN_DURATION_SHIFT ; 
 int TEGRA_CEC_RX_TIM1_DATA_BIT_SAMPLE_TIME_SHIFT ; 
 int TEGRA_CEC_RX_TIM2_END_OF_BLOCK_TIME_SHIFT ; 
 int /*<<< orphan*/  TEGRA_CEC_RX_TIMING_0 ; 
 int /*<<< orphan*/  TEGRA_CEC_RX_TIMING_1 ; 
 int /*<<< orphan*/  TEGRA_CEC_RX_TIMING_2 ; 
 int /*<<< orphan*/  TEGRA_CEC_SW_CONTROL ; 
 int TEGRA_CEC_TX_TIM0_BUS_ERROR_LO_TIME_SHIFT ; 
 int TEGRA_CEC_TX_TIM0_BUS_XITION_TIME_SHIFT ; 
 int TEGRA_CEC_TX_TIM0_START_BIT_DURATION_SHIFT ; 
 int TEGRA_CEC_TX_TIM0_START_BIT_LO_TIME_SHIFT ; 
 int TEGRA_CEC_TX_TIM1_ACK_NAK_BIT_SAMPLE_TIME_SHIFT ; 
 int TEGRA_CEC_TX_TIM1_DATA_BIT_DURATION_SHIFT ; 
 int TEGRA_CEC_TX_TIM1_HI_DATA_BIT_LO_TIME_SHIFT ; 
 int TEGRA_CEC_TX_TIM1_LO_DATA_BIT_LO_TIME_SHIFT ; 
 int TEGRA_CEC_TX_TIM2_BUS_IDLE_TIME_ADDITIONAL_FRAME_SHIFT ; 
 int TEGRA_CEC_TX_TIM2_BUS_IDLE_TIME_NEW_FRAME_SHIFT ; 
 int TEGRA_CEC_TX_TIM2_BUS_IDLE_TIME_RETRY_FRAME_SHIFT ; 
 int /*<<< orphan*/  TEGRA_CEC_TX_TIMING_0 ; 
 int /*<<< orphan*/  TEGRA_CEC_TX_TIMING_1 ; 
 int /*<<< orphan*/  TEGRA_CEC_TX_TIMING_2 ; 
 int /*<<< orphan*/  cec_write (struct tegra_cec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tegra_cec_adap_enable(struct cec_adapter *adap, bool enable)
{
	struct tegra_cec *cec = adap->priv;

	cec->rx_buf_cnt = 0;
	cec->tx_buf_cnt = 0;
	cec->tx_buf_cur = 0;

	cec_write(cec, TEGRA_CEC_HW_CONTROL, 0);
	cec_write(cec, TEGRA_CEC_INT_MASK, 0);
	cec_write(cec, TEGRA_CEC_INT_STAT, 0xffffffff);
	cec_write(cec, TEGRA_CEC_SW_CONTROL, 0);

	if (!enable)
		return 0;

	cec_write(cec, TEGRA_CEC_INPUT_FILTER, (1U << 31) | 0x20);

	cec_write(cec, TEGRA_CEC_RX_TIMING_0,
		  (0x7a << TEGRA_CEC_RX_TIM0_START_BIT_MAX_LO_TIME_SHIFT) |
		  (0x6d << TEGRA_CEC_RX_TIM0_START_BIT_MIN_LO_TIME_SHIFT) |
		  (0x93 << TEGRA_CEC_RX_TIM0_START_BIT_MAX_DURATION_SHIFT) |
		  (0x86 << TEGRA_CEC_RX_TIM0_START_BIT_MIN_DURATION_SHIFT));

	cec_write(cec, TEGRA_CEC_RX_TIMING_1,
		  (0x35 << TEGRA_CEC_RX_TIM1_DATA_BIT_MAX_LO_TIME_SHIFT) |
		  (0x21 << TEGRA_CEC_RX_TIM1_DATA_BIT_SAMPLE_TIME_SHIFT) |
		  (0x56 << TEGRA_CEC_RX_TIM1_DATA_BIT_MAX_DURATION_SHIFT) |
		  (0x40 << TEGRA_CEC_RX_TIM1_DATA_BIT_MIN_DURATION_SHIFT));

	cec_write(cec, TEGRA_CEC_RX_TIMING_2,
		  (0x50 << TEGRA_CEC_RX_TIM2_END_OF_BLOCK_TIME_SHIFT));

	cec_write(cec, TEGRA_CEC_TX_TIMING_0,
		  (0x74 << TEGRA_CEC_TX_TIM0_START_BIT_LO_TIME_SHIFT) |
		  (0x8d << TEGRA_CEC_TX_TIM0_START_BIT_DURATION_SHIFT) |
		  (0x08 << TEGRA_CEC_TX_TIM0_BUS_XITION_TIME_SHIFT) |
		  (0x71 << TEGRA_CEC_TX_TIM0_BUS_ERROR_LO_TIME_SHIFT));

	cec_write(cec, TEGRA_CEC_TX_TIMING_1,
		  (0x2f << TEGRA_CEC_TX_TIM1_LO_DATA_BIT_LO_TIME_SHIFT) |
		  (0x13 << TEGRA_CEC_TX_TIM1_HI_DATA_BIT_LO_TIME_SHIFT) |
		  (0x4b << TEGRA_CEC_TX_TIM1_DATA_BIT_DURATION_SHIFT) |
		  (0x21 << TEGRA_CEC_TX_TIM1_ACK_NAK_BIT_SAMPLE_TIME_SHIFT));

	cec_write(cec, TEGRA_CEC_TX_TIMING_2,
		  (0x07 << TEGRA_CEC_TX_TIM2_BUS_IDLE_TIME_ADDITIONAL_FRAME_SHIFT) |
		  (0x05 << TEGRA_CEC_TX_TIM2_BUS_IDLE_TIME_NEW_FRAME_SHIFT) |
		  (0x03 << TEGRA_CEC_TX_TIM2_BUS_IDLE_TIME_RETRY_FRAME_SHIFT));

	cec_write(cec, TEGRA_CEC_INT_MASK,
		  TEGRA_CEC_INT_MASK_TX_REGISTER_UNDERRUN |
		  TEGRA_CEC_INT_MASK_TX_FRAME_OR_BLOCK_NAKD |
		  TEGRA_CEC_INT_MASK_TX_ARBITRATION_FAILED |
		  TEGRA_CEC_INT_MASK_TX_BUS_ANOMALY_DETECTED |
		  TEGRA_CEC_INT_MASK_TX_FRAME_TRANSMITTED |
		  TEGRA_CEC_INT_MASK_RX_REGISTER_FULL |
		  TEGRA_CEC_INT_MASK_RX_START_BIT_DETECTED);

	cec_write(cec, TEGRA_CEC_HW_CONTROL, TEGRA_CEC_HWCTRL_TX_RX_MODE);
	return 0;
}
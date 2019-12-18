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
struct TYPE_2__ {scalar_t__ rx_status_len; } ;
struct ath_hw {int tx_trig_level; TYPE_1__ caps; } ;
struct ath_common {scalar_t__ rx_bufsize; } ;

/* Variables and functions */
 int AR_9285_PCU_TXBUF_CTRL_USABLE_SIZE ; 
 int AR_9340_PCU_TXBUF_CTRL_USABLE_SIZE ; 
 int /*<<< orphan*/  AR_AHB_MODE ; 
 int /*<<< orphan*/  AR_AHB_PREFETCH_RD_EN ; 
 int /*<<< orphan*/  AR_FTRIG ; 
 int /*<<< orphan*/  AR_PCU_TXBUF_CTRL ; 
 int AR_PCU_TXBUF_CTRL_USABLE_SIZE ; 
 int /*<<< orphan*/  AR_RXBP_THRESH ; 
 int /*<<< orphan*/  AR_RXBP_THRESH_HP ; 
 int /*<<< orphan*/  AR_RXBP_THRESH_LP ; 
 int /*<<< orphan*/  AR_RXCFG ; 
 int /*<<< orphan*/  AR_RXCFG_DMASZ_128B ; 
 int /*<<< orphan*/  AR_RXCFG_DMASZ_MASK ; 
 int /*<<< orphan*/  AR_RXFIFO_CFG ; 
 int /*<<< orphan*/  AR_SREV_9271 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9285 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9340_13_OR_LATER (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_TXCFG ; 
 int /*<<< orphan*/  AR_TXCFG_DMASZ_128B ; 
 int /*<<< orphan*/  AR_TXCFG_DMASZ_MASK ; 
 int /*<<< orphan*/  ENABLE_REGWRITE_BUFFER (struct ath_hw*) ; 
 int /*<<< orphan*/  REGWRITE_BUFFER_FLUSH (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_RMW (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_reset_txstatus_ring (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_rx_bufsize (struct ath_hw*,scalar_t__) ; 

__attribute__((used)) static inline void ath9k_hw_set_dma(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	int txbuf_size;

	ENABLE_REGWRITE_BUFFER(ah);

	/*
	 * set AHB_MODE not to do cacheline prefetches
	*/
	if (!AR_SREV_9300_20_OR_LATER(ah))
		REG_SET_BIT(ah, AR_AHB_MODE, AR_AHB_PREFETCH_RD_EN);

	/*
	 * let mac dma reads be in 128 byte chunks
	 */
	REG_RMW(ah, AR_TXCFG, AR_TXCFG_DMASZ_128B, AR_TXCFG_DMASZ_MASK);

	REGWRITE_BUFFER_FLUSH(ah);

	/*
	 * Restore TX Trigger Level to its pre-reset value.
	 * The initial value depends on whether aggregation is enabled, and is
	 * adjusted whenever underruns are detected.
	 */
	if (!AR_SREV_9300_20_OR_LATER(ah))
		REG_RMW_FIELD(ah, AR_TXCFG, AR_FTRIG, ah->tx_trig_level);

	ENABLE_REGWRITE_BUFFER(ah);

	/*
	 * let mac dma writes be in 128 byte chunks
	 */
	REG_RMW(ah, AR_RXCFG, AR_RXCFG_DMASZ_128B, AR_RXCFG_DMASZ_MASK);

	/*
	 * Setup receive FIFO threshold to hold off TX activities
	 */
	REG_WRITE(ah, AR_RXFIFO_CFG, 0x200);

	if (AR_SREV_9300_20_OR_LATER(ah)) {
		REG_RMW_FIELD(ah, AR_RXBP_THRESH, AR_RXBP_THRESH_HP, 0x1);
		REG_RMW_FIELD(ah, AR_RXBP_THRESH, AR_RXBP_THRESH_LP, 0x1);

		ath9k_hw_set_rx_bufsize(ah, common->rx_bufsize -
			ah->caps.rx_status_len);
	}

	/*
	 * reduce the number of usable entries in PCU TXBUF to avoid
	 * wrap around issues.
	 */
	if (AR_SREV_9285(ah)) {
		/* For AR9285 the number of Fifos are reduced to half.
		 * So set the usable tx buf size also to half to
		 * avoid data/delimiter underruns
		 */
		txbuf_size = AR_9285_PCU_TXBUF_CTRL_USABLE_SIZE;
	} else if (AR_SREV_9340_13_OR_LATER(ah)) {
		/* Uses fewer entries for AR934x v1.3+ to prevent rx overruns */
		txbuf_size = AR_9340_PCU_TXBUF_CTRL_USABLE_SIZE;
	} else {
		txbuf_size = AR_PCU_TXBUF_CTRL_USABLE_SIZE;
	}

	if (!AR_SREV_9271(ah))
		REG_WRITE(ah, AR_PCU_TXBUF_CTRL, txbuf_size);

	REGWRITE_BUFFER_FLUSH(ah);

	if (AR_SREV_9300_20_OR_LATER(ah))
		ath9k_hw_reset_txstatus_ring(ah);
}
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
struct seq_file {int /*<<< orphan*/  private; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_softc {struct ath_hw* sc_ah; } ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ AR_CR ; 
 scalar_t__ AR_DMADBG_0 ; 
 int /*<<< orphan*/  AR_MACMISC ; 
 int AR_MACMISC_DMA_OBS_LINE_8 ; 
 int AR_MACMISC_DMA_OBS_S ; 
 int AR_MACMISC_MISC_OBS_BUS_1 ; 
 int AR_MACMISC_MISC_OBS_BUS_MSB_S ; 
 scalar_t__ AR_OBS_BUS_1 ; 
 int ATH9K_NUM_DMA_DEBUG_REGS ; 
 int ATH9K_NUM_QUEUES ; 
 int REG_READ_D (struct ath_hw*,scalar_t__) ; 
 int /*<<< orphan*/  REG_WRITE_D (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 struct ieee80211_hw* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int read_file_dma(struct seq_file *file, void *data)
{
	struct ieee80211_hw *hw = dev_get_drvdata(file->private);
	struct ath_softc *sc = hw->priv;
	struct ath_hw *ah = sc->sc_ah;
	u32 val[ATH9K_NUM_DMA_DEBUG_REGS];
	int i, qcuOffset = 0, dcuOffset = 0;
	u32 *qcuBase = &val[0], *dcuBase = &val[4];

	ath9k_ps_wakeup(sc);

	REG_WRITE_D(ah, AR_MACMISC,
		  ((AR_MACMISC_DMA_OBS_LINE_8 << AR_MACMISC_DMA_OBS_S) |
		   (AR_MACMISC_MISC_OBS_BUS_1 <<
		    AR_MACMISC_MISC_OBS_BUS_MSB_S)));

	seq_puts(file, "Raw DMA Debug values:\n");

	for (i = 0; i < ATH9K_NUM_DMA_DEBUG_REGS; i++) {
		if (i % 4 == 0)
			seq_puts(file, "\n");

		val[i] = REG_READ_D(ah, AR_DMADBG_0 + (i * sizeof(u32)));
		seq_printf(file, "%d: %08x ", i, val[i]);
	}

	seq_puts(file, "\n\n");
	seq_puts(file, "Num QCU: chain_st fsp_ok fsp_st DCU: chain_st\n");

	for (i = 0; i < ATH9K_NUM_QUEUES; i++, qcuOffset += 4, dcuOffset += 5) {
		if (i == 8) {
			qcuOffset = 0;
			qcuBase++;
		}

		if (i == 6) {
			dcuOffset = 0;
			dcuBase++;
		}

		seq_printf(file, "%2d          %2x      %1x     %2x           %2x\n",
			   i, (*qcuBase & (0x7 << qcuOffset)) >> qcuOffset,
			   (*qcuBase & (0x8 << qcuOffset)) >> (qcuOffset + 3),
			   (val[2] & (0x7 << (i * 3))) >> (i * 3),
			   (*dcuBase & (0x1f << dcuOffset)) >> dcuOffset);
	}

	seq_puts(file, "\n");

	seq_printf(file, "qcu_stitch state:   %2x    qcu_fetch state:        %2x\n",
		   (val[3] & 0x003c0000) >> 18, (val[3] & 0x03c00000) >> 22);
	seq_printf(file, "qcu_complete state: %2x    dcu_complete state:     %2x\n",
		   (val[3] & 0x1c000000) >> 26, (val[6] & 0x3));
	seq_printf(file, "dcu_arb state:      %2x    dcu_fp state:           %2x\n",
		   (val[5] & 0x06000000) >> 25, (val[5] & 0x38000000) >> 27);
	seq_printf(file, "chan_idle_dur:     %3d    chan_idle_dur_valid:     %1d\n",
		   (val[6] & 0x000003fc) >> 2, (val[6] & 0x00000400) >> 10);
	seq_printf(file, "txfifo_valid_0:      %1d    txfifo_valid_1:          %1d\n",
		   (val[6] & 0x00000800) >> 11, (val[6] & 0x00001000) >> 12);
	seq_printf(file, "txfifo_dcu_num_0:   %2d    txfifo_dcu_num_1:       %2d\n",
		   (val[6] & 0x0001e000) >> 13, (val[6] & 0x001e0000) >> 17);

	seq_printf(file, "pcu observe: 0x%x\n", REG_READ_D(ah, AR_OBS_BUS_1));
	seq_printf(file, "AR_CR: 0x%x\n", REG_READ_D(ah, AR_CR));

	ath9k_ps_restore(sc);

	return 0;
}
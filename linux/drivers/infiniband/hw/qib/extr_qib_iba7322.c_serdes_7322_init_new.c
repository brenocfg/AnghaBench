#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct qib_pportdata {TYPE_1__* cpspec; TYPE_3__* dd; int /*<<< orphan*/  hw_pidx; } ;
struct TYPE_7__ {TYPE_2__* cspec; } ;
struct TYPE_6__ {scalar_t__ r1; } ;
struct TYPE_5__ {int qdr_dfe_on; } ;

/* Variables and functions */
 int BMASK (int,int) ; 
 int /*<<< orphan*/  IBSD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBSD_TX_DEEMPHASIS_OVERRIDE_0 ; 
 scalar_t__ IS_QME (TYPE_3__*) ; 
 int LE2_DEFAULT ; 
 int LE2_QME ; 
 unsigned long long QDR_STATIC_ADAPT_DOWN ; 
 unsigned long long QDR_STATIC_ADAPT_DOWN_R1 ; 
 int SERDES_CHANS ; 
 unsigned long long SYM_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ahb_mod (TYPE_3__*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  ibsd_wr_allchans (struct qib_pportdata*,int,int,int) ; 
 int /*<<< orphan*/  init_txdds_table (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  krp_static_adapt_dis (int) ; 
 int /*<<< orphan*/  krp_tx_deemph_override ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qib_write_kreg_port (struct qib_pportdata*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  reset_tx_deemphasis_override ; 
 int /*<<< orphan*/  serdes_7322_los_enable (struct qib_pportdata*,int) ; 
 int /*<<< orphan*/  time_is_before_jiffies (unsigned long) ; 

__attribute__((used)) static int serdes_7322_init_new(struct qib_pportdata *ppd)
{
	unsigned long tend;
	u32 le_val, rxcaldone;
	int chan, chan_done = (1 << SERDES_CHANS) - 1;

	/* Clear cmode-override, may be set from older driver */
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 10, 0 << 14, 1 << 14);

	/* ensure no tx overrides from earlier driver loads */
	qib_write_kreg_port(ppd, krp_tx_deemph_override,
		SYM_MASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
		reset_tx_deemphasis_override));

	/* START OF LSI SUGGESTED SERDES BRINGUP */
	/* Reset - Calibration Setup */
	/*       Stop DFE adaptaion */
	ibsd_wr_allchans(ppd, 1, 0, BMASK(9, 1));
	/*       Disable LE1 */
	ibsd_wr_allchans(ppd, 13, 0, BMASK(5, 5));
	/*       Disable autoadapt for LE1 */
	ibsd_wr_allchans(ppd, 1, 0, BMASK(15, 15));
	/*       Disable LE2 */
	ibsd_wr_allchans(ppd, 13, 0, BMASK(6, 6));
	/*       Disable VGA */
	ibsd_wr_allchans(ppd, 5, 0, BMASK(0, 0));
	/*       Disable AFE Offset Cancel */
	ibsd_wr_allchans(ppd, 12, 0, BMASK(12, 12));
	/*       Disable Timing Loop */
	ibsd_wr_allchans(ppd, 2, 0, BMASK(3, 3));
	/*       Disable Frequency Loop */
	ibsd_wr_allchans(ppd, 2, 0, BMASK(4, 4));
	/*       Disable Baseline Wander Correction */
	ibsd_wr_allchans(ppd, 13, 0, BMASK(13, 13));
	/*       Disable RX Calibration */
	ibsd_wr_allchans(ppd, 4, 0, BMASK(10, 10));
	/*       Disable RX Offset Calibration */
	ibsd_wr_allchans(ppd, 12, 0, BMASK(4, 4));
	/*       Select BB CDR */
	ibsd_wr_allchans(ppd, 2, (1 << 15), BMASK(15, 15));
	/*       CDR Step Size */
	ibsd_wr_allchans(ppd, 5, 0, BMASK(9, 8));
	/*       Enable phase Calibration */
	ibsd_wr_allchans(ppd, 12, (1 << 5), BMASK(5, 5));
	/*       DFE Bandwidth [2:14-12] */
	ibsd_wr_allchans(ppd, 2, (4 << 12), BMASK(14, 12));
	/*       DFE Config (4 taps only) */
	ibsd_wr_allchans(ppd, 16, 0, BMASK(1, 0));
	/*       Gain Loop Bandwidth */
	if (!ppd->dd->cspec->r1) {
		ibsd_wr_allchans(ppd, 12, 1 << 12, BMASK(12, 12));
		ibsd_wr_allchans(ppd, 12, 2 << 8, BMASK(11, 8));
	} else {
		ibsd_wr_allchans(ppd, 19, (3 << 11), BMASK(13, 11));
	}
	/*       Baseline Wander Correction Gain [13:4-0] (leave as default) */
	/*       Baseline Wander Correction Gain [3:7-5] (leave as default) */
	/*       Data Rate Select [5:7-6] (leave as default) */
	/*       RX Parallel Word Width [3:10-8] (leave as default) */

	/* RX REST */
	/*       Single- or Multi-channel reset */
	/*       RX Analog reset */
	/*       RX Digital reset */
	ibsd_wr_allchans(ppd, 0, 0, BMASK(15, 13));
	msleep(20);
	/*       RX Analog reset */
	ibsd_wr_allchans(ppd, 0, (1 << 14), BMASK(14, 14));
	msleep(20);
	/*       RX Digital reset */
	ibsd_wr_allchans(ppd, 0, (1 << 13), BMASK(13, 13));
	msleep(20);

	/* setup LoS params; these are subsystem, so chan == 5 */
	/* LoS filter threshold_count on, ch 0-3, set to 8 */
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 5, 8 << 11, BMASK(14, 11));
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 7, 8 << 4, BMASK(7, 4));
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 8, 8 << 11, BMASK(14, 11));
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 10, 8 << 4, BMASK(7, 4));

	/* LoS filter threshold_count off, ch 0-3, set to 4 */
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 6, 4 << 0, BMASK(3, 0));
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 7, 4 << 8, BMASK(11, 8));
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 9, 4 << 0, BMASK(3, 0));
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 10, 4 << 8, BMASK(11, 8));

	/* LoS filter select enabled */
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 9, 1 << 15, 1 << 15);

	/* LoS target data:  SDR=4, DDR=2, QDR=1 */
	ibsd_wr_allchans(ppd, 14, (1 << 3), BMASK(5, 3)); /* QDR */
	ibsd_wr_allchans(ppd, 20, (2 << 10), BMASK(12, 10)); /* DDR */
	ibsd_wr_allchans(ppd, 20, (4 << 13), BMASK(15, 13)); /* SDR */

	/* Turn on LOS on initial SERDES init */
	serdes_7322_los_enable(ppd, 1);
	/* FLoop LOS gate: PPM filter  enabled */
	ibsd_wr_allchans(ppd, 38, 0 << 10, 1 << 10);

	/* RX LATCH CALIBRATION */
	/*       Enable Eyefinder Phase Calibration latch */
	ibsd_wr_allchans(ppd, 15, 1, BMASK(0, 0));
	/*       Enable RX Offset Calibration latch */
	ibsd_wr_allchans(ppd, 12, (1 << 4), BMASK(4, 4));
	msleep(20);
	/*       Start Calibration */
	ibsd_wr_allchans(ppd, 4, (1 << 10), BMASK(10, 10));
	tend = jiffies + msecs_to_jiffies(500);
	while (chan_done && !time_is_before_jiffies(tend)) {
		msleep(20);
		for (chan = 0; chan < SERDES_CHANS; ++chan) {
			rxcaldone = ahb_mod(ppd->dd, IBSD(ppd->hw_pidx),
					    (chan + (chan >> 1)),
					    25, 0, 0);
			if ((~rxcaldone & (u32)BMASK(9, 9)) == 0 &&
			    (~chan_done & (1 << chan)) == 0)
				chan_done &= ~(1 << chan);
		}
	}
	if (chan_done) {
		pr_info("Serdes %d calibration not done after .5 sec: 0x%x\n",
			 IBSD(ppd->hw_pidx), chan_done);
	} else {
		for (chan = 0; chan < SERDES_CHANS; ++chan) {
			rxcaldone = ahb_mod(ppd->dd, IBSD(ppd->hw_pidx),
					    (chan + (chan >> 1)),
					    25, 0, 0);
			if ((~rxcaldone & (u32)BMASK(10, 10)) == 0)
				pr_info("Serdes %d chan %d calibration failed\n",
					IBSD(ppd->hw_pidx), chan);
		}
	}

	/*       Turn off Calibration */
	ibsd_wr_allchans(ppd, 4, 0, BMASK(10, 10));
	msleep(20);

	/* BRING RX UP */
	/*       Set LE2 value (May be overridden in qsfp_7322_event) */
	le_val = IS_QME(ppd->dd) ? LE2_QME : LE2_DEFAULT;
	ibsd_wr_allchans(ppd, 13, (le_val << 7), BMASK(9, 7));
	/*       Set LE2 Loop bandwidth */
	ibsd_wr_allchans(ppd, 3, (7 << 5), BMASK(7, 5));
	/*       Enable LE2 */
	ibsd_wr_allchans(ppd, 13, (1 << 6), BMASK(6, 6));
	msleep(20);
	/*       Enable H0 only */
	ibsd_wr_allchans(ppd, 1, 1, BMASK(9, 1));
	/* gain hi stop 32 (22) (6:1) lo stop 7 (10:7) target 22 (13) (15:11) */
	le_val = (ppd->dd->cspec->r1 || IS_QME(ppd->dd)) ? 0xb6c0 : 0x6bac;
	ibsd_wr_allchans(ppd, 21, le_val, 0xfffe);
	/*       Enable VGA */
	ibsd_wr_allchans(ppd, 5, 0, BMASK(0, 0));
	msleep(20);
	/*       Set Frequency Loop Bandwidth */
	ibsd_wr_allchans(ppd, 2, (15 << 5), BMASK(8, 5));
	/*       Enable Frequency Loop */
	ibsd_wr_allchans(ppd, 2, (1 << 4), BMASK(4, 4));
	/*       Set Timing Loop Bandwidth */
	ibsd_wr_allchans(ppd, 2, 0, BMASK(11, 9));
	/*       Enable Timing Loop */
	ibsd_wr_allchans(ppd, 2, (1 << 3), BMASK(3, 3));
	msleep(50);
	/*       Enable DFE
	 *       Set receive adaptation mode.  SDR and DDR adaptation are
	 *       always on, and QDR is initially enabled; later disabled.
	 */
	qib_write_kreg_port(ppd, krp_static_adapt_dis(0), 0ULL);
	qib_write_kreg_port(ppd, krp_static_adapt_dis(1), 0ULL);
	qib_write_kreg_port(ppd, krp_static_adapt_dis(2),
			    ppd->dd->cspec->r1 ?
			    QDR_STATIC_ADAPT_DOWN_R1 : QDR_STATIC_ADAPT_DOWN);
	ppd->cpspec->qdr_dfe_on = 1;
	/*       Disable LE1  */
	ibsd_wr_allchans(ppd, 13, (0 << 5), (1 << 5));
	/*       Disable auto adapt for LE1 */
	ibsd_wr_allchans(ppd, 1, (0 << 15), BMASK(15, 15));
	msleep(20);
	/*       Enable AFE Offset Cancel */
	ibsd_wr_allchans(ppd, 12, (1 << 12), BMASK(12, 12));
	/*       Enable Baseline Wander Correction */
	ibsd_wr_allchans(ppd, 12, (1 << 13), BMASK(13, 13));
	/* Termination: rxtermctrl_r2d addr 11 bits [12:11] = 1 */
	ibsd_wr_allchans(ppd, 11, (1 << 11), BMASK(12, 11));
	/* VGA output common mode */
	ibsd_wr_allchans(ppd, 12, (3 << 2), BMASK(3, 2));

	/*
	 * Initialize the Tx DDS tables.  Also done every QSFP event,
	 * for adapters with QSFP
	 */
	init_txdds_table(ppd, 0);

	return 0;
}
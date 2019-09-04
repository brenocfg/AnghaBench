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
struct qib_pportdata {TYPE_3__* dd; TYPE_1__* cpspec; int /*<<< orphan*/  hw_pidx; } ;
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
 unsigned long long SYM_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahb_mod (TYPE_3__*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  ibsd_wr_allchans (struct qib_pportdata*,int,int,int) ; 
 int /*<<< orphan*/  init_txdds_table (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krp_static_adapt_dis (int) ; 
 int /*<<< orphan*/  krp_tx_deemph_override ; 
 int /*<<< orphan*/  qib_write_kreg_port (struct qib_pportdata*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  reset_tx_deemphasis_override ; 
 int /*<<< orphan*/  serdes_7322_los_enable (struct qib_pportdata*,int) ; 

__attribute__((used)) static int serdes_7322_init_old(struct qib_pportdata *ppd)
{
	u32 le_val;

	/*
	 * Initialize the Tx DDS tables.  Also done every QSFP event,
	 * for adapters with QSFP
	 */
	init_txdds_table(ppd, 0);

	/* ensure no tx overrides from earlier driver loads */
	qib_write_kreg_port(ppd, krp_tx_deemph_override,
		SYM_MASK(IBSD_TX_DEEMPHASIS_OVERRIDE_0,
		reset_tx_deemphasis_override));

	/* Patch some SerDes defaults to "Better for IB" */
	/* Timing Loop Bandwidth: cdr_timing[11:9] = 0 */
	ibsd_wr_allchans(ppd, 2, 0, BMASK(11, 9));

	/* Termination: rxtermctrl_r2d addr 11 bits [12:11] = 1 */
	ibsd_wr_allchans(ppd, 11, (1 << 11), BMASK(12, 11));
	/* Enable LE2: rxle2en_r2a addr 13 bit [6] = 1 */
	ibsd_wr_allchans(ppd, 13, (1 << 6), (1 << 6));

	/* May be overridden in qsfp_7322_event */
	le_val = IS_QME(ppd->dd) ? LE2_QME : LE2_DEFAULT;
	ibsd_wr_allchans(ppd, 13, (le_val << 7), BMASK(9, 7));

	/* enable LE1 adaptation for all but QME, which is disabled */
	le_val = IS_QME(ppd->dd) ? 0 : 1;
	ibsd_wr_allchans(ppd, 13, (le_val << 5), (1 << 5));

	/* Clear cmode-override, may be set from older driver */
	ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), 5, 10, 0 << 14, 1 << 14);

	/* Timing Recovery: rxtapsel addr 5 bits [9:8] = 0 */
	ibsd_wr_allchans(ppd, 5, (0 << 8), BMASK(9, 8));

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

	serdes_7322_los_enable(ppd, 1);

	/* rxbistena; set 0 to avoid effects of it switch later */
	ibsd_wr_allchans(ppd, 9, 0 << 15, 1 << 15);

	/* Configure 4 DFE taps, and only they adapt */
	ibsd_wr_allchans(ppd, 16, 0 << 0, BMASK(1, 0));

	/* gain hi stop 32 (22) (6:1) lo stop 7 (10:7) target 22 (13) (15:11) */
	le_val = (ppd->dd->cspec->r1 || IS_QME(ppd->dd)) ? 0xb6c0 : 0x6bac;
	ibsd_wr_allchans(ppd, 21, le_val, 0xfffe);

	/*
	 * Set receive adaptation mode.  SDR and DDR adaptation are
	 * always on, and QDR is initially enabled; later disabled.
	 */
	qib_write_kreg_port(ppd, krp_static_adapt_dis(0), 0ULL);
	qib_write_kreg_port(ppd, krp_static_adapt_dis(1), 0ULL);
	qib_write_kreg_port(ppd, krp_static_adapt_dis(2),
			    ppd->dd->cspec->r1 ?
			    QDR_STATIC_ADAPT_DOWN_R1 : QDR_STATIC_ADAPT_DOWN);
	ppd->cpspec->qdr_dfe_on = 1;

	/* FLoop LOS gate: PPM filter  enabled */
	ibsd_wr_allchans(ppd, 38, 0 << 10, 1 << 10);

	/* rx offset center enabled */
	ibsd_wr_allchans(ppd, 12, 1 << 4, 1 << 4);

	if (!ppd->dd->cspec->r1) {
		ibsd_wr_allchans(ppd, 12, 1 << 12, 1 << 12);
		ibsd_wr_allchans(ppd, 12, 2 << 8, 0x0f << 8);
	}

	/* Set the frequency loop bandwidth to 15 */
	ibsd_wr_allchans(ppd, 2, 15 << 5, BMASK(8, 5));

	return 0;
}
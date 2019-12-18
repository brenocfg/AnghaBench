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
typedef  int u_short ;
typedef  int u_char ;
struct TYPE_2__ {int /*<<< orphan*/  hw_state; int /*<<< orphan*/  is_imask; int /*<<< orphan*/  hw_is_64bit; } ;
struct s_smc {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B0_CTRL ; 
 int /*<<< orphan*/  B0_LED ; 
 int /*<<< orphan*/  B0_TST_CTRL ; 
 int /*<<< orphan*/  B2_WDOG_INI ; 
 int /*<<< orphan*/  B4_R1_F ; 
 int /*<<< orphan*/  B5_XA_F ; 
 int /*<<< orphan*/  B5_XS_F ; 
 int CTRL_HPI_CLR ; 
 int CTRL_HPI_SET ; 
 int CTRL_MRST_CLR ; 
 int CTRL_RST_CLR ; 
 int CTRL_RST_SET ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_MDREG1 ; 
 int FM_MINIT ; 
 int /*<<< orphan*/  GET_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISR_MASK ; 
 int LED_GA_OFF ; 
 int LED_GB_OFF ; 
 int LED_MY_ON ; 
 int /*<<< orphan*/  MS2BCLK (int) ; 
 int /*<<< orphan*/  PCI_C (int /*<<< orphan*/ ) ; 
 int PCI_ERRBITS ; 
 int /*<<< orphan*/  PCI_REVISION_ID ; 
 int /*<<< orphan*/  PCI_STATUS ; 
 int RX_WATERMARK ; 
 int SK_ML_ID_1 ; 
 int SK_ML_ID_2 ; 
 int /*<<< orphan*/  SK_UNUSED (int) ; 
 int /*<<< orphan*/  STOPPED ; 
 int /*<<< orphan*/  TRUE ; 
 int TST_CFG_WRITE_OFF ; 
 int TST_CFG_WRITE_ON ; 
 int TX_WATERMARK ; 
 int /*<<< orphan*/  hwt_quick_read (struct s_smc*) ; 
 int /*<<< orphan*/  hwt_wait_time (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int inp (int /*<<< orphan*/ ) ; 
 int inpw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outpd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smt_stop_watchdog (struct s_smc*) ; 

__attribute__((used)) static void card_start(struct s_smc *smc)
{
	int i ;
#ifdef	PCI
	u_char	rev_id ;
	u_short word;
#endif

	smt_stop_watchdog(smc) ;

#ifdef	PCI
	/*
	 * make sure no transfer activity is pending
	 */
	outpw(FM_A(FM_MDREG1),FM_MINIT) ;
	outp(ADDR(B0_CTRL), CTRL_HPI_SET) ;
	hwt_wait_time(smc,hwt_quick_read(smc),MS2BCLK(10)) ;
	/*
	 * now reset everything
	 */
	outp(ADDR(B0_CTRL),CTRL_RST_SET) ;	/* reset for all chips */
	i = (int) inp(ADDR(B0_CTRL)) ;		/* do dummy read */
	SK_UNUSED(i) ;				/* Make LINT happy. */
	outp(ADDR(B0_CTRL), CTRL_RST_CLR) ;

	/*
	 * Reset all bits in the PCI STATUS register
	 */
	outp(ADDR(B0_TST_CTRL), TST_CFG_WRITE_ON) ;	/* enable for writes */
	word = inpw(PCI_C(PCI_STATUS)) ;
	outpw(PCI_C(PCI_STATUS), word | PCI_ERRBITS) ;
	outp(ADDR(B0_TST_CTRL), TST_CFG_WRITE_OFF) ;	/* disable writes */

	/*
	 * Release the reset of all the State machines
	 * Release Master_Reset
	 * Release HPI_SM_Reset
	 */
	outp(ADDR(B0_CTRL), CTRL_MRST_CLR|CTRL_HPI_CLR) ;

	/*
	 * determine the adapter type
	 * Note: Do it here, because some drivers may call card_start() once
	 *	 at very first before any other initialization functions is
	 *	 executed.
	 */
	rev_id = inp(PCI_C(PCI_REVISION_ID)) ;
	if ((rev_id & 0xf0) == SK_ML_ID_1 || (rev_id & 0xf0) == SK_ML_ID_2) {
		smc->hw.hw_is_64bit = TRUE ;
	} else {
		smc->hw.hw_is_64bit = FALSE ;
	}

	/*
	 * Watermark initialization
	 */
	if (!smc->hw.hw_is_64bit) {
		outpd(ADDR(B4_R1_F), RX_WATERMARK) ;
		outpd(ADDR(B5_XA_F), TX_WATERMARK) ;
		outpd(ADDR(B5_XS_F), TX_WATERMARK) ;
	}

	outp(ADDR(B0_CTRL),CTRL_RST_CLR) ;	/* clear the reset chips */
	outp(ADDR(B0_LED),LED_GA_OFF|LED_MY_ON|LED_GB_OFF) ; /* ye LED on */

	/* init the timer value for the watch dog 2,5 minutes */
	outpd(ADDR(B2_WDOG_INI),0x6FC23AC0) ;

	/* initialize the ISR mask */
	smc->hw.is_imask = ISR_MASK ;
	smc->hw.hw_state = STOPPED ;
#endif
	GET_PAGE(0) ;		/* necessary for BOOT */
}
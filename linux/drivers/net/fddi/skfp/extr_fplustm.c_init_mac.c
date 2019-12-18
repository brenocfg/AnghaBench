#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_short ;
typedef  int u_long ;
struct TYPE_5__ {int mdr2init; int rx_mode; int mdr3init; int frselreg_init; } ;
struct TYPE_8__ {int /*<<< orphan*/  hw_state; int /*<<< orphan*/  hw_is_64bit; TYPE_1__ fp; } ;
struct TYPE_7__ {TYPE_2__* m; } ;
struct s_smc {TYPE_4__ hw; TYPE_3__ mib; } ;
struct TYPE_6__ {int fddiMACT_Max; int fddiMACTvxValue; int /*<<< orphan*/  fddiMACT_Req; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B0_CTRL ; 
 int /*<<< orphan*/  B0_R1_CSR ; 
 int /*<<< orphan*/  B0_XA_CSR ; 
 int /*<<< orphan*/  B0_XS_CSR ; 
 int /*<<< orphan*/  B4_R1_F ; 
 int /*<<< orphan*/  B5_XA_F ; 
 int /*<<< orphan*/  B5_XS_F ; 
 int /*<<< orphan*/  CSR_CLR_RESET ; 
 int /*<<< orphan*/  CSR_SET_RESET ; 
 int /*<<< orphan*/  CTRL_HPI_CLR ; 
 int /*<<< orphan*/  CTRL_HPI_SET ; 
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_CMDREG1 ; 
 int /*<<< orphan*/  FM_FRMTHR ; 
 int /*<<< orphan*/  FM_FRSELREG ; 
 int FM_ICLLA0 ; 
 int FM_ICLLR ; 
 int FM_ICLLS ; 
 int /*<<< orphan*/  FM_MDREG1 ; 
 int /*<<< orphan*/  FM_MDREG2 ; 
 int /*<<< orphan*/  FM_MDREG3 ; 
 int FM_MINIT ; 
 int FM_MMEMACT ; 
 int FM_SELRA ; 
 int /*<<< orphan*/  FM_TMAX ; 
 int /*<<< orphan*/  FM_TVX ; 
 int /*<<< orphan*/  FM_UNLCKDLY ; 
 size_t MAC0 ; 
 int MB ; 
 int MDR1INIT ; 
 int /*<<< orphan*/  MS2BCLK (int) ; 
 int /*<<< orphan*/  RX_WATERMARK ; 
 int /*<<< orphan*/  STARTED ; 
 int /*<<< orphan*/  STOPPED ; 
 int /*<<< orphan*/  TX_WATERMARK ; 
 scalar_t__ US2BCLK (int) ; 
 int /*<<< orphan*/  build_claim_beacon (struct s_smc*,int /*<<< orphan*/ ) ; 
 int hwt_quick_read (struct s_smc*) ; 
 int /*<<< orphan*/  hwt_wait_time (struct s_smc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_ram (struct s_smc*) ; 
 int /*<<< orphan*/  init_rbc (struct s_smc*) ; 
 int /*<<< orphan*/  init_rx (struct s_smc*) ; 
 int /*<<< orphan*/  init_tx (struct s_smc*) ; 
 int /*<<< orphan*/  mac_drv_repair_descr (struct s_smc*) ; 
 int /*<<< orphan*/  outp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outpd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtm_init (struct s_smc*) ; 
 int /*<<< orphan*/  set_formac_addr (struct s_smc*) ; 
 int /*<<< orphan*/  smt_split_up_fifo (struct s_smc*) ; 

__attribute__((used)) static int init_mac(struct s_smc *smc, int all)
{
	u_short	t_max,x ;
	u_long	time=0 ;

	/*
	 * clear memory
	 */
	outpw(FM_A(FM_MDREG1),FM_MINIT) ;	/* FORMAC+ init mode */
	set_formac_addr(smc) ;
	outpw(FM_A(FM_MDREG1),FM_MMEMACT) ;	/* FORMAC+ memory activ mode */
	/* Note: Mode register 2 is set here, incase parity is enabled. */
	outpw(FM_A(FM_MDREG2),smc->hw.fp.mdr2init) ;

	if (all) {
		init_ram(smc) ;
	}
	else {
		/*
		 * reset the HPI, the Master and the BMUs
		 */
		outp(ADDR(B0_CTRL), CTRL_HPI_SET) ;
		time = hwt_quick_read(smc) ;
	}

	/*
	 * set all pointers, frames etc
	 */
	smt_split_up_fifo(smc) ;

	init_tx(smc) ;
	init_rx(smc) ;
	init_rbc(smc) ;

	build_claim_beacon(smc,smc->mib.m[MAC0].fddiMACT_Req) ;

	/* set RX threshold */
	/* see Errata #SN2 Phantom receive overflow */
	outpw(FM_A(FM_FRMTHR),14<<12) ;		/* switch on */

	/* set formac work mode */
	outpw(FM_A(FM_MDREG1),MDR1INIT | FM_SELRA | smc->hw.fp.rx_mode) ;
	outpw(FM_A(FM_MDREG2),smc->hw.fp.mdr2init) ;
	outpw(FM_A(FM_MDREG3),smc->hw.fp.mdr3init) ;
	outpw(FM_A(FM_FRSELREG),smc->hw.fp.frselreg_init) ;

	/* set timer */
	/*
	 * errata #22 fplus:
	 * T_MAX must not be FFFE
	 * or one of FFDF, FFB8, FF91 (-0x27 etc..)
	 */
	t_max = (u_short)(smc->mib.m[MAC0].fddiMACT_Max/32) ;
	x = t_max/0x27 ;
	x *= 0x27 ;
	if ((t_max == 0xfffe) || (t_max - x == 0x16))
		t_max-- ;
	outpw(FM_A(FM_TMAX),(u_short)t_max) ;

	/* BugFix for report #10204 */
	if (smc->mib.m[MAC0].fddiMACTvxValue < (u_long) (- US2BCLK(52))) {
		outpw(FM_A(FM_TVX), (u_short) (- US2BCLK(52))/255 & MB) ;
	} else {
		outpw(FM_A(FM_TVX),
			(u_short)((smc->mib.m[MAC0].fddiMACTvxValue/255) & MB)) ;
	}

	outpw(FM_A(FM_CMDREG1),FM_ICLLS) ;	/* clear s-frame lock */
	outpw(FM_A(FM_CMDREG1),FM_ICLLA0) ;	/* clear a-frame lock */
	outpw(FM_A(FM_CMDREG1),FM_ICLLR);	/* clear receive lock */

	/* Auto unlock receice threshold for receive queue 1 and 2 */
	outpw(FM_A(FM_UNLCKDLY),(0xff|(0xff<<8))) ;

	rtm_init(smc) ;				/* RT-Monitor */

	if (!all) {
		/*
		 * after 10ms, reset the BMUs and repair the rings
		 */
		hwt_wait_time(smc,time,MS2BCLK(10)) ;
		outpd(ADDR(B0_R1_CSR),CSR_SET_RESET) ;
		outpd(ADDR(B0_XA_CSR),CSR_SET_RESET) ;
		outpd(ADDR(B0_XS_CSR),CSR_SET_RESET) ;
		outp(ADDR(B0_CTRL), CTRL_HPI_CLR) ;
		outpd(ADDR(B0_R1_CSR),CSR_CLR_RESET) ;
		outpd(ADDR(B0_XA_CSR),CSR_CLR_RESET) ;
		outpd(ADDR(B0_XS_CSR),CSR_CLR_RESET) ;
		if (!smc->hw.hw_is_64bit) {
			outpd(ADDR(B4_R1_F), RX_WATERMARK) ;
			outpd(ADDR(B5_XA_F), TX_WATERMARK) ;
			outpd(ADDR(B5_XS_F), TX_WATERMARK) ;
		}
		smc->hw.hw_state = STOPPED ;
		mac_drv_repair_descr(smc) ;
	}
	smc->hw.hw_state = STARTED ;

	return 0;
}
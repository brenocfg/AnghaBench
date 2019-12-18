#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
typedef  int u_long ;
struct TYPE_11__ {int detec_count; void* isr_flag; void* leave_isr; scalar_t__ rx_break; } ;
struct TYPE_12__ {TYPE_5__ hwm; } ;
struct TYPE_10__ {scalar_t__ ev_get; scalar_t__ ev_put; } ;
struct TYPE_8__ {TYPE_1__* rx_q; } ;
struct TYPE_9__ {TYPE_2__ fp; } ;
struct s_smc {TYPE_6__ os; TYPE_4__ q; TYPE_3__ hw; } ;
struct TYPE_7__ {scalar_t__ rx_used; } ;
typedef  int /*<<< orphan*/  SMbuf ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B4_R1_CSR ; 
 int /*<<< orphan*/  B5_XA_CSR ; 
 int /*<<< orphan*/  B5_XS_CSR ; 
 int /*<<< orphan*/  CSR_IRQ_CL_C ; 
 int /*<<< orphan*/  CSR_IRQ_CL_F ; 
 int /*<<< orphan*/  CSR_IRQ_CL_P ; 
 int /*<<< orphan*/  DB_GEN (int,char*,...) ; 
 void* FALSE ; 
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_ST1L ; 
 int /*<<< orphan*/  FM_ST1U ; 
 int /*<<< orphan*/  FM_ST2L ; 
 int /*<<< orphan*/  FM_ST2U ; 
 int /*<<< orphan*/  FM_ST3L ; 
 int /*<<< orphan*/  FM_ST3U ; 
 int GET_ISR () ; 
 int /*<<< orphan*/  HWM_E0004 ; 
 int /*<<< orphan*/  HWM_E0004_MSG ; 
 int /*<<< orphan*/  HWM_E0005 ; 
 int /*<<< orphan*/  HWM_E0005_MSG ; 
 int /*<<< orphan*/  HWM_E0006 ; 
 int /*<<< orphan*/  HWM_E0006_MSG ; 
 int /*<<< orphan*/  HWM_E0007 ; 
 int /*<<< orphan*/  HWM_E0007_MSG ; 
 int IMASK_SLOW ; 
 int ISR_MASK ; 
 int IS_MINTR1 ; 
 int IS_MINTR2 ; 
 int IS_MINTR3 ; 
 int IS_PLINT1 ; 
 int IS_PLINT2 ; 
 int IS_R1_C ; 
 int IS_R1_F ; 
 int IS_R1_P ; 
 int IS_TIMINT ; 
 int IS_TOKEN ; 
 int IS_XA_C ; 
 int IS_XA_F ; 
 int IS_XS_C ; 
 int IS_XS_F ; 
 int /*<<< orphan*/  NDD_TRACE (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t QUEUE_R1 ; 
 int /*<<< orphan*/  SMT_PANIC (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 int /*<<< orphan*/  ev_dispatcher (struct s_smc*) ; 
 scalar_t__ force_irq_pending ; 
 int /*<<< orphan*/ * get_llc_rx (struct s_smc*) ; 
 int /*<<< orphan*/  inpw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_restart_tx (struct s_smc*) ; 
 int /*<<< orphan*/  mac1_irq (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac2_irq (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac3_irq (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_drv_clear_txd (struct s_smc*) ; 
 int /*<<< orphan*/  mac_drv_fill_rxd (struct s_smc*) ; 
 scalar_t__ offDepth ; 
 int /*<<< orphan*/  outpd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plc1_irq (struct s_smc*) ; 
 int /*<<< orphan*/  plc2_irq (struct s_smc*) ; 
 int /*<<< orphan*/  post_proc () ; 
 int /*<<< orphan*/  process_receive (struct s_smc*) ; 
 int /*<<< orphan*/  rtm_irq (struct s_smc*) ; 
 int /*<<< orphan*/  smt_force_irq (struct s_smc*) ; 
 int /*<<< orphan*/  smt_to_llc (struct s_smc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_irq (struct s_smc*) ; 

void fddi_isr(struct s_smc *smc)
{
	u_long		is ;		/* ISR source */
	u_short		stu, stl ;
	SMbuf		*mb ;

#ifdef	USE_BREAK_ISR
	int	force_irq ;
#endif

#ifdef	ODI2
	if (smc->os.hwm.rx_break) {
		mac_drv_fill_rxd(smc) ;
		if (smc->hw.fp.rx_q[QUEUE_R1].rx_used > 0) {
			smc->os.hwm.rx_break = 0 ;
			process_receive(smc) ;
		}
		else {
			smc->os.hwm.detec_count = 0 ;
			smt_force_irq(smc) ;
		}
	}
#endif
	smc->os.hwm.isr_flag = TRUE ;

#ifdef	USE_BREAK_ISR
	force_irq = TRUE ;
	if (smc->os.hwm.leave_isr) {
		smc->os.hwm.leave_isr = FALSE ;
		process_receive(smc) ;
	}
#endif

	while ((is = GET_ISR() & ISR_MASK)) {
		NDD_TRACE("CH0B",is,0,0) ;
		DB_GEN(7, "ISA = 0x%lx", is);

		if (is & IMASK_SLOW) {
			NDD_TRACE("CH1b",is,0,0) ;
			if (is & IS_PLINT1) {	/* PLC1 */
				plc1_irq(smc) ;
			}
			if (is & IS_PLINT2) {	/* PLC2 */
				plc2_irq(smc) ;
			}
			if (is & IS_MINTR1) {	/* FORMAC+ STU1(U/L) */
				stu = inpw(FM_A(FM_ST1U)) ;
				stl = inpw(FM_A(FM_ST1L)) ;
				DB_GEN(6, "Slow transmit complete");
				mac1_irq(smc,stu,stl) ;
			}
			if (is & IS_MINTR2) {	/* FORMAC+ STU2(U/L) */
				stu= inpw(FM_A(FM_ST2U)) ;
				stl= inpw(FM_A(FM_ST2L)) ;
				DB_GEN(6, "Slow receive complete");
				DB_GEN(7, "stl = %x : stu = %x", stl, stu);
				mac2_irq(smc,stu,stl) ;
			}
			if (is & IS_MINTR3) {	/* FORMAC+ STU3(U/L) */
				stu= inpw(FM_A(FM_ST3U)) ;
				stl= inpw(FM_A(FM_ST3L)) ;
				DB_GEN(6, "FORMAC Mode Register 3");
				mac3_irq(smc,stu,stl) ;
			}
			if (is & IS_TIMINT) {	/* Timer 82C54-2 */
				timer_irq(smc) ;
#ifdef	NDIS_OS2
				force_irq_pending = 0 ;
#endif
				/*
				 * out of RxD detection
				 */
				if (++smc->os.hwm.detec_count > 4) {
					/*
					 * check out of RxD condition
					 */
					 process_receive(smc) ;
				}
			}
			if (is & IS_TOKEN) {	/* Restricted Token Monitor */
				rtm_irq(smc) ;
			}
			if (is & IS_R1_P) {	/* Parity error rx queue 1 */
				/* clear IRQ */
				outpd(ADDR(B4_R1_CSR),CSR_IRQ_CL_P) ;
				SMT_PANIC(smc,HWM_E0004,HWM_E0004_MSG) ;
			}
			if (is & IS_R1_C) {	/* Encoding error rx queue 1 */
				/* clear IRQ */
				outpd(ADDR(B4_R1_CSR),CSR_IRQ_CL_C) ;
				SMT_PANIC(smc,HWM_E0005,HWM_E0005_MSG) ;
			}
			if (is & IS_XA_C) {	/* Encoding error async tx q */
				/* clear IRQ */
				outpd(ADDR(B5_XA_CSR),CSR_IRQ_CL_C) ;
				SMT_PANIC(smc,HWM_E0006,HWM_E0006_MSG) ;
			}
			if (is & IS_XS_C) {	/* Encoding error sync tx q */
				/* clear IRQ */
				outpd(ADDR(B5_XS_CSR),CSR_IRQ_CL_C) ;
				SMT_PANIC(smc,HWM_E0007,HWM_E0007_MSG) ;
			}
		}

		/*
		 *	Fast Tx complete Async/Sync Queue (BMU service)
		 */
		if (is & (IS_XS_F|IS_XA_F)) {
			DB_GEN(6, "Fast tx complete queue");
			/*
			 * clear IRQ, Note: no IRQ is lost, because
			 * 	we always service both queues
			 */
			outpd(ADDR(B5_XS_CSR),CSR_IRQ_CL_F) ;
			outpd(ADDR(B5_XA_CSR),CSR_IRQ_CL_F) ;
			mac_drv_clear_txd(smc) ;
			llc_restart_tx(smc) ;
		}

		/*
		 *	Fast Rx Complete (BMU service)
		 */
		if (is & IS_R1_F) {
			DB_GEN(6, "Fast receive complete");
			/* clear IRQ */
#ifndef USE_BREAK_ISR
			outpd(ADDR(B4_R1_CSR),CSR_IRQ_CL_F) ;
			process_receive(smc) ;
#else
			process_receive(smc) ;
			if (smc->os.hwm.leave_isr) {
				force_irq = FALSE ;
			} else {
				outpd(ADDR(B4_R1_CSR),CSR_IRQ_CL_F) ;
				process_receive(smc) ;
			}
#endif
		}

#ifndef	NDIS_OS2
		while ((mb = get_llc_rx(smc))) {
			smt_to_llc(smc,mb) ;
		}
#else
		if (offDepth)
			post_proc() ;

		while (!offDepth && (mb = get_llc_rx(smc))) {
			smt_to_llc(smc,mb) ;
		}

		if (!offDepth && smc->os.hwm.rx_break) {
			process_receive(smc) ;
		}
#endif
		if (smc->q.ev_get != smc->q.ev_put) {
			NDD_TRACE("CH2a",0,0,0) ;
			ev_dispatcher(smc) ;
		}
#ifdef	NDIS_OS2
		post_proc() ;
		if (offDepth) {		/* leave fddi_isr because */
			break ;		/* indications not allowed */
		}
#endif
#ifdef	USE_BREAK_ISR
		if (smc->os.hwm.leave_isr) {
			break ;		/* leave fddi_isr */
		}
#endif

		/* NOTE: when the isr is left, no rx is pending */
	}	/* end of interrupt source polling loop */

#ifdef	USE_BREAK_ISR
	if (smc->os.hwm.leave_isr && force_irq) {
		smt_force_irq(smc) ;
	}
#endif
	smc->os.hwm.isr_flag = FALSE ;
	NDD_TRACE("CH0E",0,0,0) ;
}
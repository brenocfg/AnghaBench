#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_short ;
struct TYPE_10__ {int /*<<< orphan*/  err_tkerr; int /*<<< orphan*/  err_tkiss; int /*<<< orphan*/  err_sifg_det; int /*<<< orphan*/  err_phinv; int /*<<< orphan*/  err_clm_stat; int /*<<< orphan*/  err_bec_stat; } ;
struct TYPE_13__ {int s2l; int s2u; TYPE_3__ err_stats; } ;
struct TYPE_8__ {int /*<<< orphan*/  mac_r_restart_counter; } ;
struct TYPE_14__ {TYPE_6__ fp; TYPE_1__ mac_ct; int /*<<< orphan*/  mac_ring_is_up; } ;
struct TYPE_12__ {TYPE_4__* m; } ;
struct TYPE_9__ {int /*<<< orphan*/  dup_addr_test; } ;
struct s_smc {TYPE_7__ hw; TYPE_5__ mib; TYPE_2__ r; } ;
struct TYPE_11__ {int fddiMACFrame_Ct; int fddiMACError_Ct; int fddiMACLost_Ct; int /*<<< orphan*/  fddiMACRingOp_Ct; int /*<<< orphan*/  fddiMACTvxExpired_Ct; int /*<<< orphan*/  fddiMACNotCopied_Ct; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA_FAILED ; 
 int /*<<< orphan*/  DB_RMTN (int,char*) ; 
 int /*<<< orphan*/  EVENT_RMT ; 
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_IMSK2U ; 
 int FM_SBEC ; 
 int FM_SCLM ; 
 int FM_SDUPCLM ; 
 int FM_SERRCTR ; 
 int FM_SERRSF ; 
 int FM_SFRMCTR ; 
 int FM_SHICLM ; 
 int FM_SLOCLM ; 
 int FM_SLSTCTR ; 
 int FM_SMISFRM ; 
 int FM_SMULTDA ; 
 int FM_SMYBEC ; 
 int FM_SMYCLM ; 
 int FM_SOTRBEC ; 
 int FM_SPHINV ; 
 int FM_SRBFL ; 
 int FM_SRCVOVR ; 
 int FM_SRNGOP ; 
 int FM_SSIFG ; 
 int FM_STKERR ; 
 int FM_STKISS ; 
 int FM_STRTEXP ; 
 int FM_STRTEXR ; 
 int FM_STVXEXP ; 
 size_t MAC0 ; 
 int /*<<< orphan*/  RM_DUP_ADDR ; 
 int /*<<< orphan*/  RM_MY_BEACON ; 
 int /*<<< orphan*/  RM_MY_CLAIM ; 
 int /*<<< orphan*/  RM_OTHER_BEACON ; 
 int /*<<< orphan*/  RM_RING_NON_OP ; 
 int /*<<< orphan*/  RM_RING_OP ; 
 int /*<<< orphan*/  RM_TRT_EXP ; 
 int /*<<< orphan*/  RM_TX_STATE_CHANGE ; 
 int /*<<< orphan*/  RM_VALID_CLAIM ; 
 int /*<<< orphan*/  SMT_E0114 ; 
 int /*<<< orphan*/  SMT_E0114_MSG ; 
 int /*<<< orphan*/  SMT_PANIC (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_imsk2u ; 
 int /*<<< orphan*/  mac_ring_up (struct s_smc*,int) ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_event (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smt_stat_counter (struct s_smc*,int) ; 

void mac2_irq(struct s_smc *smc, u_short code_s2u, u_short code_s2l)
{
	u_short	change_s2l ;
	u_short	change_s2u ;

	/* (jd) 22-Feb-1999
	 * Restart 2_DMax Timer after end of claiming or beaconing
	 */
	if (code_s2u & (FM_SCLM|FM_SHICLM|FM_SBEC|FM_SOTRBEC)) {
		queue_event(smc,EVENT_RMT,RM_TX_STATE_CHANGE) ;
	}
	else if (code_s2l & (FM_STKISS)) {
		queue_event(smc,EVENT_RMT,RM_TX_STATE_CHANGE) ;
	}

	/*
	 * XOR current st bits with the last to avoid useless RMT event queuing
	 */
	change_s2l = smc->hw.fp.s2l ^ code_s2l ;
	change_s2u = smc->hw.fp.s2u ^ code_s2u ;

	if ((change_s2l & FM_SRNGOP) ||
		(!smc->hw.mac_ring_is_up && ((code_s2l & FM_SRNGOP)))) {
		if (code_s2l & FM_SRNGOP) {
			mac_ring_up(smc,1) ;
			queue_event(smc,EVENT_RMT,RM_RING_OP) ;
			smc->mib.m[MAC0].fddiMACRingOp_Ct++ ;
		}
		else {
			mac_ring_up(smc,0) ;
			queue_event(smc,EVENT_RMT,RM_RING_NON_OP) ;
		}
		goto mac2_end ;
	}
	if (code_s2l & FM_SMISFRM) {	/* missed frame */
		smc->mib.m[MAC0].fddiMACNotCopied_Ct++ ;
	}
	if (code_s2u & (FM_SRCVOVR |	/* recv. FIFO overflow */
			FM_SRBFL)) {	/* recv. buffer full */
		smc->hw.mac_ct.mac_r_restart_counter++ ;
/*		formac_rcv_restart(smc) ;	*/
		smt_stat_counter(smc,1) ;
/*		goto mac2_end ;			*/
	}
	if (code_s2u & FM_SOTRBEC)
		queue_event(smc,EVENT_RMT,RM_OTHER_BEACON) ;
	if (code_s2u & FM_SMYBEC)
		queue_event(smc,EVENT_RMT,RM_MY_BEACON) ;
	if (change_s2u & code_s2u & FM_SLOCLM) {
		DB_RMTN(2, "RMT : lower claim received");
	}
	if ((code_s2u & FM_SMYCLM) && !(code_s2l & FM_SDUPCLM)) {
		/*
		 * This is my claim and that claim is not detected as a
		 * duplicate one.
		 */
		queue_event(smc,EVENT_RMT,RM_MY_CLAIM) ;
	}
	if (code_s2l & FM_SDUPCLM) {
		/*
		 * If a duplicate claim frame (same SA but T_Bid != T_Req)
		 * this flag will be set.
		 * In the RMT state machine we need a RM_VALID_CLAIM event
		 * to do the appropriate state change.
		 * RM(34c)
		 */
		queue_event(smc,EVENT_RMT,RM_VALID_CLAIM) ;
	}
	if (change_s2u & code_s2u & FM_SHICLM) {
		DB_RMTN(2, "RMT : higher claim received");
	}
	if ( (code_s2l & FM_STRTEXP) ||
	     (code_s2l & FM_STRTEXR) )
		queue_event(smc,EVENT_RMT,RM_TRT_EXP) ;
	if (code_s2l & FM_SMULTDA) {
		/*
		 * The MAC has found a 2. MAC with the same address.
		 * Signal dup_addr_test = failed to RMT state machine.
		 * RM(25)
		 */
		smc->r.dup_addr_test = DA_FAILED ;
		queue_event(smc,EVENT_RMT,RM_DUP_ADDR) ;
	}
	if (code_s2u & FM_SBEC)
		smc->hw.fp.err_stats.err_bec_stat++ ;
	if (code_s2u & FM_SCLM)
		smc->hw.fp.err_stats.err_clm_stat++ ;
	if (code_s2l & FM_STVXEXP)
		smc->mib.m[MAC0].fddiMACTvxExpired_Ct++ ;
	if ((code_s2u & (FM_SBEC|FM_SCLM))) {
		if (!(change_s2l & FM_SRNGOP) && (smc->hw.fp.s2l & FM_SRNGOP)) {
			mac_ring_up(smc,0) ;
			queue_event(smc,EVENT_RMT,RM_RING_NON_OP) ;

			mac_ring_up(smc,1) ;
			queue_event(smc,EVENT_RMT,RM_RING_OP) ;
			smc->mib.m[MAC0].fddiMACRingOp_Ct++ ;
		}
	}
	if (code_s2l & FM_SPHINV)
		smc->hw.fp.err_stats.err_phinv++ ;
	if (code_s2l & FM_SSIFG)
		smc->hw.fp.err_stats.err_sifg_det++ ;
	if (code_s2l & FM_STKISS)
		smc->hw.fp.err_stats.err_tkiss++ ;
	if (code_s2l & FM_STKERR)
		smc->hw.fp.err_stats.err_tkerr++ ;
	if (code_s2l & FM_SFRMCTR)
		smc->mib.m[MAC0].fddiMACFrame_Ct += 0x10000L ;
	if (code_s2l & FM_SERRCTR)
		smc->mib.m[MAC0].fddiMACError_Ct += 0x10000L ;
	if (code_s2l & FM_SLSTCTR)
		smc->mib.m[MAC0].fddiMACLost_Ct  += 0x10000L ;
	if (code_s2u & FM_SERRSF) {
		SMT_PANIC(smc,SMT_E0114, SMT_E0114_MSG) ;
	}
mac2_end:
	/* notice old status */
	smc->hw.fp.s2l = code_s2l ;
	smc->hw.fp.s2u = code_s2u ;
	outpw(FM_A(FM_IMSK2U),~mac_imsk2u) ;
}
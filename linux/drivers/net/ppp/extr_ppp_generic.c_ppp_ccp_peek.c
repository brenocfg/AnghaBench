#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {unsigned char* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;
struct ppp {int xstate; int rstate; int flags; int /*<<< orphan*/  xc_state; TYPE_3__* xcomp; int /*<<< orphan*/  rc_state; TYPE_2__* rcomp; int /*<<< orphan*/  debug; TYPE_1__ file; int /*<<< orphan*/  mru; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* comp_reset ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* comp_init ) (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* decomp_reset ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* decomp_init ) (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int CCP_CODE (unsigned char*) ; 
#define  CCP_CONFACK 132 
#define  CCP_CONFREQ 131 
 int CCP_HDRLEN ; 
 int CCP_LENGTH (unsigned char*) ; 
 int CCP_OPT_LENGTH (unsigned char*) ; 
 int CCP_OPT_MINLEN ; 
#define  CCP_RESETACK 130 
#define  CCP_TERMACK 129 
#define  CCP_TERMREQ 128 
 int SC_CCP_OPEN ; 
 int SC_CCP_UP ; 
 int SC_COMP_RUN ; 
 int SC_DC_ERROR ; 
 int SC_DC_FERROR ; 
 int SC_DECOMP_RUN ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ppp_ccp_peek(struct ppp *ppp, struct sk_buff *skb, int inbound)
{
	unsigned char *dp;
	int len;

	if (!pskb_may_pull(skb, CCP_HDRLEN + 2))
		return;	/* no header */
	dp = skb->data + 2;

	switch (CCP_CODE(dp)) {
	case CCP_CONFREQ:

		/* A ConfReq starts negotiation of compression
		 * in one direction of transmission,
		 * and hence brings it down...but which way?
		 *
		 * Remember:
		 * A ConfReq indicates what the sender would like to receive
		 */
		if(inbound)
			/* He is proposing what I should send */
			ppp->xstate &= ~SC_COMP_RUN;
		else
			/* I am proposing to what he should send */
			ppp->rstate &= ~SC_DECOMP_RUN;

		break;

	case CCP_TERMREQ:
	case CCP_TERMACK:
		/*
		 * CCP is going down, both directions of transmission
		 */
		ppp->rstate &= ~SC_DECOMP_RUN;
		ppp->xstate &= ~SC_COMP_RUN;
		break;

	case CCP_CONFACK:
		if ((ppp->flags & (SC_CCP_OPEN | SC_CCP_UP)) != SC_CCP_OPEN)
			break;
		len = CCP_LENGTH(dp);
		if (!pskb_may_pull(skb, len + 2))
			return;		/* too short */
		dp += CCP_HDRLEN;
		len -= CCP_HDRLEN;
		if (len < CCP_OPT_MINLEN || len < CCP_OPT_LENGTH(dp))
			break;
		if (inbound) {
			/* we will start receiving compressed packets */
			if (!ppp->rc_state)
				break;
			if (ppp->rcomp->decomp_init(ppp->rc_state, dp, len,
					ppp->file.index, 0, ppp->mru, ppp->debug)) {
				ppp->rstate |= SC_DECOMP_RUN;
				ppp->rstate &= ~(SC_DC_ERROR | SC_DC_FERROR);
			}
		} else {
			/* we will soon start sending compressed packets */
			if (!ppp->xc_state)
				break;
			if (ppp->xcomp->comp_init(ppp->xc_state, dp, len,
					ppp->file.index, 0, ppp->debug))
				ppp->xstate |= SC_COMP_RUN;
		}
		break;

	case CCP_RESETACK:
		/* reset the [de]compressor */
		if ((ppp->flags & SC_CCP_UP) == 0)
			break;
		if (inbound) {
			if (ppp->rc_state && (ppp->rstate & SC_DECOMP_RUN)) {
				ppp->rcomp->decomp_reset(ppp->rc_state);
				ppp->rstate &= ~SC_DC_ERROR;
			}
		} else {
			if (ppp->xc_state && (ppp->xstate & SC_COMP_RUN))
				ppp->xcomp->comp_reset(ppp->xc_state);
		}
		break;
	}
}
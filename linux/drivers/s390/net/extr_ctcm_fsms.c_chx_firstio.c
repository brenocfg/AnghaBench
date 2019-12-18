#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {struct ctcm_priv* ml_priv; } ;
struct ctcm_priv {int /*<<< orphan*/  fsm; } ;
struct channel {scalar_t__ protocol; struct net_device* netdev; int /*<<< orphan*/  flags; int /*<<< orphan*/  timer; TYPE_2__* ccw; int /*<<< orphan*/  cdev; TYPE_1__* trans_skb; int /*<<< orphan*/  id; scalar_t__ sense_rc; } ;
typedef  int /*<<< orphan*/  fsm_instance ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_4__ {int count; } ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ CHANNEL_DIRECTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTCM_DBF_TEXT_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  CTCM_FUNTAIL ; 
 int /*<<< orphan*/  CTCM_INITIAL_BLOCKLEN ; 
 scalar_t__ CTCM_PROTO_OS390 ; 
 scalar_t__ CTCM_PROTO_S390 ; 
 scalar_t__ CTCM_READ ; 
 int /*<<< orphan*/  CTCM_TIME_5_SEC ; 
 scalar_t__ CTCM_WRITE ; 
 int /*<<< orphan*/  CTC_DBF_DEBUG ; 
 int /*<<< orphan*/  CTC_DBF_NOTICE ; 
 int /*<<< orphan*/  CTC_EVENT_TIMER ; 
 int CTC_STATE_RXINIT ; 
 int CTC_STATE_SETUPWAIT ; 
 int CTC_STATE_TXIDLE ; 
 int CTC_STATE_TXINIT ; 
 int /*<<< orphan*/  DEV_EVENT_RXUP ; 
 int /*<<< orphan*/  DEV_EVENT_TXUP ; 
 int /*<<< orphan*/  TRACE ; 
 int ccw_device_start (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chx_rxidle (int /*<<< orphan*/ *,int,void*) ; 
 int /*<<< orphan*/  ctcm_ccw_check_rc (struct channel*,int,char*) ; 
 scalar_t__ ctcm_checkalloc_buffer (struct channel*) ; 
 int /*<<< orphan*/  fsm_addtimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct channel*) ; 
 int /*<<< orphan*/  fsm_deltimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int fsm_getstate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_newstate (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void chx_firstio(fsm_instance *fi, int event, void *arg)
{
	int rc;
	struct channel *ch = arg;
	int fsmstate = fsm_getstate(fi);

	CTCM_DBF_TEXT_(TRACE, CTC_DBF_NOTICE,
		"%s(%s) : %02x",
		CTCM_FUNTAIL, ch->id, fsmstate);

	ch->sense_rc = 0;	/* reset unit check report control */
	if (fsmstate == CTC_STATE_TXIDLE)
		CTCM_DBF_TEXT_(TRACE, CTC_DBF_DEBUG,
			"%s(%s): remote side issued READ?, init.\n",
				CTCM_FUNTAIL, ch->id);
	fsm_deltimer(&ch->timer);
	if (ctcm_checkalloc_buffer(ch))
		return;
	if ((fsmstate == CTC_STATE_SETUPWAIT) &&
	    (ch->protocol == CTCM_PROTO_OS390)) {
		/* OS/390 resp. z/OS */
		if (CHANNEL_DIRECTION(ch->flags) == CTCM_READ) {
			*((__u16 *)ch->trans_skb->data) = CTCM_INITIAL_BLOCKLEN;
			fsm_addtimer(&ch->timer, CTCM_TIME_5_SEC,
				     CTC_EVENT_TIMER, ch);
			chx_rxidle(fi, event, arg);
		} else {
			struct net_device *dev = ch->netdev;
			struct ctcm_priv *priv = dev->ml_priv;
			fsm_newstate(fi, CTC_STATE_TXIDLE);
			fsm_event(priv->fsm, DEV_EVENT_TXUP, dev);
		}
		return;
	}
	/*
	 * Don't setup a timer for receiving the initial RX frame
	 * if in compatibility mode, since VM TCP delays the initial
	 * frame until it has some data to send.
	 */
	if ((CHANNEL_DIRECTION(ch->flags) == CTCM_WRITE) ||
	    (ch->protocol != CTCM_PROTO_S390))
		fsm_addtimer(&ch->timer, CTCM_TIME_5_SEC, CTC_EVENT_TIMER, ch);

	*((__u16 *)ch->trans_skb->data) = CTCM_INITIAL_BLOCKLEN;
	ch->ccw[1].count = 2;	/* Transfer only length */

	fsm_newstate(fi, (CHANNEL_DIRECTION(ch->flags) == CTCM_READ)
		     ? CTC_STATE_RXINIT : CTC_STATE_TXINIT);
	rc = ccw_device_start(ch->cdev, &ch->ccw[0], 0, 0xff, 0);
	if (rc != 0) {
		fsm_deltimer(&ch->timer);
		fsm_newstate(fi, CTC_STATE_SETUPWAIT);
		ctcm_ccw_check_rc(ch, rc, "init IO");
	}
	/*
	 * If in compatibility mode since we don't setup a timer, we
	 * also signal RX channel up immediately. This enables us
	 * to send packets early which in turn usually triggers some
	 * reply from VM TCP which brings up the RX channel to it's
	 * final state.
	 */
	if ((CHANNEL_DIRECTION(ch->flags) == CTCM_READ) &&
	    (ch->protocol == CTCM_PROTO_S390)) {
		struct net_device *dev = ch->netdev;
		struct ctcm_priv *priv = dev->ml_priv;
		fsm_event(priv->fsm, DEV_EVENT_RXUP, dev);
	}
}
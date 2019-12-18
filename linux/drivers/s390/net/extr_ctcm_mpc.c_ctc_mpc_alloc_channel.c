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
struct net_device {int /*<<< orphan*/  name; struct ctcm_priv* ml_priv; } ;
struct mpc_group {void (* allochanfunc ) (int,int) ;int port_num; int port_persist; int alloc_called; int send_qllc_disc; int allocchan_callback_retries; int group_max_buflen; int /*<<< orphan*/  fsm; int /*<<< orphan*/ * saved_xid2; int /*<<< orphan*/  outstanding_xid7_p2; int /*<<< orphan*/  outstanding_xid7; int /*<<< orphan*/  outstanding_xid2; int /*<<< orphan*/  timer; } ;
struct ctcm_priv {int /*<<< orphan*/  fsm; struct mpc_group* mpcg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTCM_DBF_TEXT_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTCM_FUNTAIL ; 
 int /*<<< orphan*/  CTC_DBF_INFO ; 
 int /*<<< orphan*/  DEV_EVENT_START ; 
 int /*<<< orphan*/  MPCG_EVENT_INOP ; 
#define  MPCG_STATE_INOP 131 
#define  MPCG_STATE_READY 130 
#define  MPCG_STATE_RESET 129 
#define  MPCG_STATE_XID0IOWAIT 128 
 int /*<<< orphan*/  MPC_SETUP ; 
 int /*<<< orphan*/  ctcm_open (struct net_device*) ; 
 struct net_device* ctcmpc_get_dev (int) ; 
 int /*<<< orphan*/  fsm_deltimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int fsm_getstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsm_getstate_str (int /*<<< orphan*/ ) ; 
 void stub1 (int,int) ; 

int ctc_mpc_alloc_channel(int port_num, void (*callback)(int, int))
{
	struct net_device *dev;
	struct mpc_group *grp;
	struct ctcm_priv *priv;

	dev = ctcmpc_get_dev(port_num);
	if (dev == NULL)
		return 1;
	priv = dev->ml_priv;
	grp = priv->mpcg;

	grp->allochanfunc = callback;
	grp->port_num = port_num;
	grp->port_persist = 1;

	CTCM_DBF_TEXT_(MPC_SETUP, CTC_DBF_INFO,
			"%s(%s): state=%s",
			CTCM_FUNTAIL, dev->name, fsm_getstate_str(grp->fsm));

	switch (fsm_getstate(grp->fsm)) {
	case MPCG_STATE_INOP:
		/* Group is in the process of terminating */
		grp->alloc_called = 1;
		break;
	case MPCG_STATE_RESET:
		/* MPC Group will transition to state		  */
		/* MPCG_STATE_XID2INITW iff the minimum number	  */
		/* of 1 read and 1 write channel have successfully*/
		/* activated					  */
		/*fsm_newstate(grp->fsm, MPCG_STATE_XID2INITW);*/
		if (callback)
			grp->send_qllc_disc = 1;
		/* Else, fall through */
	case MPCG_STATE_XID0IOWAIT:
		fsm_deltimer(&grp->timer);
		grp->outstanding_xid2 = 0;
		grp->outstanding_xid7 = 0;
		grp->outstanding_xid7_p2 = 0;
		grp->saved_xid2 = NULL;
		if (callback)
			ctcm_open(dev);
		fsm_event(priv->fsm, DEV_EVENT_START, dev);
		break;
	case MPCG_STATE_READY:
		/* XID exchanges completed after PORT was activated */
		/* Link station already active			    */
		/* Maybe timing issue...retry callback		    */
		grp->allocchan_callback_retries++;
		if (grp->allocchan_callback_retries < 4) {
			if (grp->allochanfunc)
				grp->allochanfunc(grp->port_num,
						  grp->group_max_buflen);
		} else {
			/* there are problems...bail out	    */
			/* there may be a state mismatch so restart */
			fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);
			grp->allocchan_callback_retries = 0;
		}
		break;
	}

	return 0;
}
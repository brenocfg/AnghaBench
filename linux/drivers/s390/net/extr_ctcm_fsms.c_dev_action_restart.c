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
struct net_device {int /*<<< orphan*/  dev; struct ctcm_priv* ml_priv; } ;
struct ctcm_priv {int /*<<< orphan*/  restart_timer; TYPE_1__* mpcg; int /*<<< orphan*/  fsm; } ;
typedef  int /*<<< orphan*/  fsm_instance ;
struct TYPE_2__ {int /*<<< orphan*/  fsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTCMY_DBF_DEV_NAME (int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int CTCM_TIME_1_SEC ; 
 int CTCM_TIME_5_SEC ; 
 int /*<<< orphan*/  DEV_EVENT_START ; 
 int /*<<< orphan*/  DEV_EVENT_STOP ; 
 scalar_t__ IS_MPC (struct ctcm_priv*) ; 
 int /*<<< orphan*/  MPCG_STATE_RESET ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  dev_action_stop (int /*<<< orphan*/ *,int,void*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fsm_addtimer (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  fsm_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  fsm_newstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dev_action_restart(fsm_instance *fi, int event, void *arg)
{
	int restart_timer;
	struct net_device *dev = arg;
	struct ctcm_priv *priv = dev->ml_priv;

	CTCMY_DBF_DEV_NAME(TRACE, dev, "");

	if (IS_MPC(priv)) {
		restart_timer = CTCM_TIME_1_SEC;
	} else {
		restart_timer = CTCM_TIME_5_SEC;
	}
	dev_info(&dev->dev, "Restarting device\n");

	dev_action_stop(fi, event, arg);
	fsm_event(priv->fsm, DEV_EVENT_STOP, dev);
	if (IS_MPC(priv))
		fsm_newstate(priv->mpcg->fsm, MPCG_STATE_RESET);

	/* going back into start sequence too quickly can	  */
	/* result in the other side becoming unreachable   due	  */
	/* to sense reported when IO is aborted			  */
	fsm_addtimer(&priv->restart_timer, restart_timer,
			DEV_EVENT_START, dev);
}
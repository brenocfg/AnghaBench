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
struct net_device {struct ctcm_priv* ml_priv; } ;
struct ctcm_priv {int /*<<< orphan*/  fsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTCMY_DBF_DEV_NAME (int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  DEV_EVENT_STOP ; 
 int /*<<< orphan*/  IS_MPC (struct ctcm_priv*) ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  fsm_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

int ctcm_close(struct net_device *dev)
{
	struct ctcm_priv *priv = dev->ml_priv;

	CTCMY_DBF_DEV_NAME(SETUP, dev, "");
	if (!IS_MPC(priv))
		fsm_event(priv->fsm, DEV_EVENT_STOP, dev);
	return 0;
}
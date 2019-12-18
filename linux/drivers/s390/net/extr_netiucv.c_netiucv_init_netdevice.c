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
struct netiucv_priv {int /*<<< orphan*/  fsm; int /*<<< orphan*/  conn; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_FSM_LEN ; 
 int /*<<< orphan*/  DEV_STATE_STOPPED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IUCV_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 int /*<<< orphan*/  NR_DEV_EVENTS ; 
 int /*<<< orphan*/  NR_DEV_STATES ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dev_alloc_name (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_event_names ; 
 int /*<<< orphan*/  dev_fsm ; 
 int /*<<< orphan*/  dev_state_names ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  fsm_newstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_fsm (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_fsm (int /*<<< orphan*/ ) ; 
 struct netiucv_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netiucv_new_connection (struct net_device*,char*,char*) ; 
 int /*<<< orphan*/  netiucv_setup_netdevice ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  setup ; 

__attribute__((used)) static struct net_device *netiucv_init_netdevice(char *username, char *userdata)
{
	struct netiucv_priv *privptr;
	struct net_device *dev;

	dev = alloc_netdev(sizeof(struct netiucv_priv), "iucv%d",
			   NET_NAME_UNKNOWN, netiucv_setup_netdevice);
	if (!dev)
		return NULL;
	rtnl_lock();
	if (dev_alloc_name(dev, dev->name) < 0)
		goto out_netdev;

	privptr = netdev_priv(dev);
	privptr->fsm = init_fsm("netiucvdev", dev_state_names,
				dev_event_names, NR_DEV_STATES, NR_DEV_EVENTS,
				dev_fsm, DEV_FSM_LEN, GFP_KERNEL);
	if (!privptr->fsm)
		goto out_netdev;

	privptr->conn = netiucv_new_connection(dev, username, userdata);
	if (!privptr->conn) {
		IUCV_DBF_TEXT(setup, 2, "NULL from netiucv_new_connection\n");
		goto out_fsm;
	}
	fsm_newstate(privptr->fsm, DEV_STATE_STOPPED);
	return dev;

out_fsm:
	kfree_fsm(privptr->fsm);
out_netdev:
	rtnl_unlock();
	free_netdev(dev);
	return NULL;
}
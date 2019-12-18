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
struct netiucv_priv {int /*<<< orphan*/  fsm; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_EVENT_START ; 
 int /*<<< orphan*/  fsm_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 struct netiucv_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int netiucv_open(struct net_device *dev)
{
	struct netiucv_priv *priv = netdev_priv(dev);

	fsm_event(priv->fsm, DEV_EVENT_START, dev);
	return 0;
}
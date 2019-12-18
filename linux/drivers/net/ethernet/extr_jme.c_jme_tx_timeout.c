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
struct net_device {int dummy; } ;
struct jme_adapter {int /*<<< orphan*/  old_cmd; int /*<<< orphan*/  flags; scalar_t__ phylink; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_FLAG_SSET ; 
 int /*<<< orphan*/  jme_reset_link (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_reset_phy_processor (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_set_link_ksettings (struct net_device*,int /*<<< orphan*/ *) ; 
 struct jme_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
jme_tx_timeout(struct net_device *netdev)
{
	struct jme_adapter *jme = netdev_priv(netdev);

	jme->phylink = 0;
	jme_reset_phy_processor(jme);
	if (test_bit(JME_FLAG_SSET, &jme->flags))
		jme_set_link_ksettings(netdev, &jme->old_cmd);

	/*
	 * Force to Reset the link again
	 */
	jme_reset_link(jme);
}
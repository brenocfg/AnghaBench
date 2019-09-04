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
struct dynpcc_info {scalar_t__ cnt; void* attempt; void* cur; } ;
struct jme_adapter {int /*<<< orphan*/  jme_rx; int /*<<< orphan*/  flags; struct dynpcc_info dpi; } ;
struct ethtool_coalesce {scalar_t__ use_adaptive_rx_coalesce; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  JME_FLAG_POLL ; 
 void* PCC_P1 ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jme_interrupt_mode (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_set_rx_pcc (struct jme_adapter*,void*) ; 
 struct jme_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
jme_set_coalesce(struct net_device *netdev, struct ethtool_coalesce *ecmd)
{
	struct jme_adapter *jme = netdev_priv(netdev);
	struct dynpcc_info *dpi = &(jme->dpi);

	if (netif_running(netdev))
		return -EBUSY;

	if (ecmd->use_adaptive_rx_coalesce &&
	    test_bit(JME_FLAG_POLL, &jme->flags)) {
		clear_bit(JME_FLAG_POLL, &jme->flags);
		jme->jme_rx = netif_rx;
		dpi->cur		= PCC_P1;
		dpi->attempt		= PCC_P1;
		dpi->cnt		= 0;
		jme_set_rx_pcc(jme, PCC_P1);
		jme_interrupt_mode(jme);
	} else if (!(ecmd->use_adaptive_rx_coalesce) &&
		   !(test_bit(JME_FLAG_POLL, &jme->flags))) {
		set_bit(JME_FLAG_POLL, &jme->flags);
		jme->jme_rx = netif_receive_skb;
		jme_interrupt_mode(jme);
	}

	return 0;
}
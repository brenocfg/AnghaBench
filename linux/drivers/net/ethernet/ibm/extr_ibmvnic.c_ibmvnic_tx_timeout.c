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
struct ibmvnic_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VNIC_RESET_TIMEOUT ; 
 int /*<<< orphan*/  ibmvnic_reset (struct ibmvnic_adapter*,int /*<<< orphan*/ ) ; 
 struct ibmvnic_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ibmvnic_tx_timeout(struct net_device *dev)
{
	struct ibmvnic_adapter *adapter = netdev_priv(dev);

	ibmvnic_reset(adapter, VNIC_RESET_TIMEOUT);
}
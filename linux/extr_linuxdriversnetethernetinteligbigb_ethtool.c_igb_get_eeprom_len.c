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
struct net_device {int dummy; } ;
struct TYPE_3__ {int word_size; } ;
struct TYPE_4__ {TYPE_1__ nvm; } ;
struct igb_adapter {TYPE_2__ hw; } ;

/* Variables and functions */
 struct igb_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int igb_get_eeprom_len(struct net_device *netdev)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	return adapter->hw.nvm.word_size * 2;
}
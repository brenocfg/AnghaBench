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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct l2t_entry {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct adapter* netdev2adap (struct net_device*) ; 
 struct l2t_entry* t4_l2t_alloc_switching (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct l2t_entry *cxgb4_l2t_alloc_switching(struct net_device *dev, u16 vlan,
					    u8 port, u8 *dmac)
{
	struct adapter *adap = netdev2adap(dev);

	return t4_l2t_alloc_switching(adap, vlan, port, dmac);
}
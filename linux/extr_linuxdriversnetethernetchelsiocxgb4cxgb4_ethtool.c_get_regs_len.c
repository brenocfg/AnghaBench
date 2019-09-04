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
struct adapter {int dummy; } ;

/* Variables and functions */
 struct adapter* netdev2adap (struct net_device*) ; 
 int t4_get_regs_len (struct adapter*) ; 

__attribute__((used)) static int get_regs_len(struct net_device *dev)
{
	struct adapter *adap = netdev2adap(dev);

	return t4_get_regs_len(adap);
}
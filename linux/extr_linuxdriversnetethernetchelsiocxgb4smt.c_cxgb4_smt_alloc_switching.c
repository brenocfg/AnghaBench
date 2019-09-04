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
struct smt_entry {int dummy; } ;
struct net_device {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct adapter* netdev2adap (struct net_device*) ; 
 struct smt_entry* t4_smt_alloc_switching (struct adapter*,int,int /*<<< orphan*/ *) ; 

struct smt_entry *cxgb4_smt_alloc_switching(struct net_device *dev, u8 *smac)
{
	struct adapter *adap = netdev2adap(dev);

	return t4_smt_alloc_switching(adap, 0x0, smac);
}
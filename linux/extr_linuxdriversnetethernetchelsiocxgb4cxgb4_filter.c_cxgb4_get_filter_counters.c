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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int get_filter_count (struct adapter*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct adapter* netdev2adap (struct net_device*) ; 

int cxgb4_get_filter_counters(struct net_device *dev, unsigned int fidx,
			      u64 *hitcnt, u64 *bytecnt, bool hash)
{
	struct adapter *adapter = netdev2adap(dev);

	return get_filter_count(adapter, fidx, hitcnt, bytecnt, hash);
}
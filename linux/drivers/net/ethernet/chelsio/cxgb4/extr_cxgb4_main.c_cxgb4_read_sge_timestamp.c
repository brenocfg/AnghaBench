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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGE_TIMESTAMP_HI_A ; 
 int /*<<< orphan*/  SGE_TIMESTAMP_LO_A ; 
 scalar_t__ TSVAL_G (scalar_t__) ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 scalar_t__ t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

u64 cxgb4_read_sge_timestamp(struct net_device *dev)
{
	u32 hi, lo;
	struct adapter *adap;

	adap = netdev2adap(dev);
	lo = t4_read_reg(adap, SGE_TIMESTAMP_LO_A);
	hi = TSVAL_G(t4_read_reg(adap, SGE_TIMESTAMP_HI_A));

	return ((u64)hi << 32) | (u64)lo;
}
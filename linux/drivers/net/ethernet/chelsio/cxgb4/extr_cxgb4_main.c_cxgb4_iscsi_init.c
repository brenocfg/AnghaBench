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
 unsigned int HPZ0_V (unsigned int const) ; 
 unsigned int HPZ1_V (unsigned int const) ; 
 unsigned int HPZ2_V (unsigned int const) ; 
 unsigned int HPZ3_V (unsigned int const) ; 
 int /*<<< orphan*/  ULP_RX_ISCSI_PSZ_A ; 
 int /*<<< orphan*/  ULP_RX_ISCSI_TAGMASK_A ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,unsigned int) ; 

void cxgb4_iscsi_init(struct net_device *dev, unsigned int tag_mask,
		      const unsigned int *pgsz_order)
{
	struct adapter *adap = netdev2adap(dev);

	t4_write_reg(adap, ULP_RX_ISCSI_TAGMASK_A, tag_mask);
	t4_write_reg(adap, ULP_RX_ISCSI_PSZ_A, HPZ0_V(pgsz_order[0]) |
		     HPZ1_V(pgsz_order[1]) | HPZ2_V(pgsz_order[2]) |
		     HPZ3_V(pgsz_order[3]));
}
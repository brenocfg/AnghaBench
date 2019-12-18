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
struct cphy {TYPE_1__* ops; } ;
struct adapter {int dummy; } ;
struct TYPE_4__ {struct cphy phy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* intr_enable ) (struct cphy*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  A_XGM_INT_ENABLE ; 
 int /*<<< orphan*/  XGM_INTR_MASK ; 
 int /*<<< orphan*/  XGM_REG (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* adap2pinfo (struct adapter*,int) ; 
 int /*<<< orphan*/  stub1 (struct cphy*) ; 
 int /*<<< orphan*/  t3_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void t3_port_intr_enable(struct adapter *adapter, int idx)
{
	struct cphy *phy = &adap2pinfo(adapter, idx)->phy;

	t3_write_reg(adapter, XGM_REG(A_XGM_INT_ENABLE, idx), XGM_INTR_MASK);
	t3_read_reg(adapter, XGM_REG(A_XGM_INT_ENABLE, idx)); /* flush */
	phy->ops->intr_enable(phy);
}
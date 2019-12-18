#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qlcnic_host_sds_ring {int /*<<< orphan*/  crb_intr_mask; } ;
struct qlcnic_adapter {int flags; TYPE_1__* ahw; } ;
struct TYPE_2__ {int /*<<< orphan*/  diag_test; } ;

/* Variables and functions */
 int QLCNIC_MSIX_ENABLED ; 
 scalar_t__ qlcnic_check_multi_tx (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
qlcnic_82xx_disable_sds_intr(struct qlcnic_adapter *adapter,
			     struct qlcnic_host_sds_ring *sds_ring)
{
	if (qlcnic_check_multi_tx(adapter) &&
	    !adapter->ahw->diag_test &&
	    (adapter->flags & QLCNIC_MSIX_ENABLED))
		writel(0x1, sds_ring->crb_intr_mask);
	else
		writel(0, sds_ring->crb_intr_mask);
}
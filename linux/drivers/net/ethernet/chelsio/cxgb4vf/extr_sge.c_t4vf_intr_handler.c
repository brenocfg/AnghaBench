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
struct adapter {int flags; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CXGB4VF_USING_MSI ; 
 int CXGB4VF_USING_MSIX ; 
 int /*<<< orphan*/  t4vf_intr_msi ; 
 int /*<<< orphan*/  t4vf_sge_intr_msix ; 

irq_handler_t t4vf_intr_handler(struct adapter *adapter)
{
	BUG_ON((adapter->flags &
	       (CXGB4VF_USING_MSIX | CXGB4VF_USING_MSI)) == 0);
	if (adapter->flags & CXGB4VF_USING_MSIX)
		return t4vf_sge_intr_msix;
	else
		return t4vf_intr_msi;
}
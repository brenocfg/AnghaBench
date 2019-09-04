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
struct TYPE_2__ {scalar_t__ rev; } ;
struct adapter {int flags; TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int USING_MSI ; 
 int USING_MSIX ; 
 int /*<<< orphan*/  t3_intr ; 
 int /*<<< orphan*/  t3_intr_msi ; 
 int /*<<< orphan*/  t3_intr_msi_napi ; 
 int /*<<< orphan*/  t3_sge_intr_msix ; 
 int /*<<< orphan*/  t3_sge_intr_msix_napi ; 
 int /*<<< orphan*/  t3b_intr ; 
 int /*<<< orphan*/  t3b_intr_napi ; 

irq_handler_t t3_intr_handler(struct adapter *adap, int polling)
{
	if (adap->flags & USING_MSIX)
		return polling ? t3_sge_intr_msix_napi : t3_sge_intr_msix;
	if (adap->flags & USING_MSI)
		return polling ? t3_intr_msi_napi : t3_intr_msi;
	if (adap->params.rev > 0)
		return polling ? t3b_intr_napi : t3b_intr;
	return t3_intr;
}
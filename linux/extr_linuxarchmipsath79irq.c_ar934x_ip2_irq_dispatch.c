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
typedef  int u32 ;
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int AR934X_PCIE_WMAC_INT_PCIE_ALL ; 
 int AR934X_PCIE_WMAC_INT_WMAC_ALL ; 
 int /*<<< orphan*/  AR934X_RESET_REG_PCIE_WMAC_INT_STATUS ; 
 int /*<<< orphan*/  ATH79_IP2_IRQ (int) ; 
 int /*<<< orphan*/  ath79_ddr_wb_flush (int) ; 
 int ath79_reset_rr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spurious_interrupt () ; 

__attribute__((used)) static void ar934x_ip2_irq_dispatch(struct irq_desc *desc)
{
	u32 status;

	status = ath79_reset_rr(AR934X_RESET_REG_PCIE_WMAC_INT_STATUS);

	if (status & AR934X_PCIE_WMAC_INT_PCIE_ALL) {
		ath79_ddr_wb_flush(3);
		generic_handle_irq(ATH79_IP2_IRQ(0));
	} else if (status & AR934X_PCIE_WMAC_INT_WMAC_ALL) {
		ath79_ddr_wb_flush(4);
		generic_handle_irq(ATH79_IP2_IRQ(1));
	} else {
		spurious_interrupt();
	}
}
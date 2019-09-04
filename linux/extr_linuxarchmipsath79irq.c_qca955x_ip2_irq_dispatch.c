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
 int /*<<< orphan*/  ATH79_IP2_IRQ (int) ; 
 int QCA955X_EXT_INT_PCIE_RC1_ALL ; 
 int QCA955X_EXT_INT_WMAC_ALL ; 
 int /*<<< orphan*/  QCA955X_RESET_REG_EXT_INT_STATUS ; 
 int ath79_reset_rr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spurious_interrupt () ; 

__attribute__((used)) static void qca955x_ip2_irq_dispatch(struct irq_desc *desc)
{
	u32 status;

	status = ath79_reset_rr(QCA955X_RESET_REG_EXT_INT_STATUS);
	status &= QCA955X_EXT_INT_PCIE_RC1_ALL | QCA955X_EXT_INT_WMAC_ALL;

	if (status == 0) {
		spurious_interrupt();
		return;
	}

	if (status & QCA955X_EXT_INT_PCIE_RC1_ALL) {
		/* TODO: flush DDR? */
		generic_handle_irq(ATH79_IP2_IRQ(0));
	}

	if (status & QCA955X_EXT_INT_WMAC_ALL) {
		/* TODO: flush DDR? */
		generic_handle_irq(ATH79_IP2_IRQ(1));
	}
}
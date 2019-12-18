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
struct mtk_pcie_port {scalar_t__ base; } ;
struct irq_data {int hwirq; } ;

/* Variables and functions */
 scalar_t__ PCIE_IMSI_STATUS ; 
 struct mtk_pcie_port* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mtk_msi_ack_irq(struct irq_data *data)
{
	struct mtk_pcie_port *port = irq_data_get_irq_chip_data(data);
	u32 hwirq = data->hwirq;

	writel(1 << hwirq, port->base + PCIE_IMSI_STATUS);
}
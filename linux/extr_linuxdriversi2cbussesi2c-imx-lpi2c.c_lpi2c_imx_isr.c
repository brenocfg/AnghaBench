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
struct lpi2c_imx_struct {int /*<<< orphan*/  complete; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ LPI2C_MSR ; 
 unsigned int MSR_NDF ; 
 unsigned int MSR_RDF ; 
 unsigned int MSR_TDF ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpi2c_imx_intctrl (struct lpi2c_imx_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpi2c_imx_read_rxfifo (struct lpi2c_imx_struct*) ; 
 int /*<<< orphan*/  lpi2c_imx_write_txfifo (struct lpi2c_imx_struct*) ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static irqreturn_t lpi2c_imx_isr(int irq, void *dev_id)
{
	struct lpi2c_imx_struct *lpi2c_imx = dev_id;
	unsigned int temp;

	lpi2c_imx_intctrl(lpi2c_imx, 0);
	temp = readl(lpi2c_imx->base + LPI2C_MSR);

	if (temp & MSR_RDF)
		lpi2c_imx_read_rxfifo(lpi2c_imx);

	if (temp & MSR_TDF)
		lpi2c_imx_write_txfifo(lpi2c_imx);

	if (temp & MSR_NDF)
		complete(&lpi2c_imx->complete);

	return IRQ_HANDLED;
}
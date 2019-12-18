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
struct imx7d_adc {scalar_t__ regs; int /*<<< orphan*/  dev; int /*<<< orphan*/  completion; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ IMX7D_REG_ADC_INT_STATUS ; 
 int IMX7D_REG_ADC_INT_STATUS_CHANNEL_CONV_TIME_OUT ; 
 int IMX7D_REG_ADC_INT_STATUS_CHANNEL_INT_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  imx7d_adc_read_data (struct imx7d_adc*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t imx7d_adc_isr(int irq, void *dev_id)
{
	struct imx7d_adc *info = dev_id;
	int status;

	status = readl(info->regs + IMX7D_REG_ADC_INT_STATUS);
	if (status & IMX7D_REG_ADC_INT_STATUS_CHANNEL_INT_STATUS) {
		info->value = imx7d_adc_read_data(info);
		complete(&info->completion);

		/*
		 * The register IMX7D_REG_ADC_INT_STATUS can't clear
		 * itself after read operation, need software to write
		 * 0 to the related bit. Here we clear the channel A/B/C/D
		 * conversion finished flag.
		 */
		status &= ~IMX7D_REG_ADC_INT_STATUS_CHANNEL_INT_STATUS;
		writel(status, info->regs + IMX7D_REG_ADC_INT_STATUS);
	}

	/*
	 * If the channel A/B/C/D conversion timeout, report it and clear these
	 * timeout flags.
	 */
	if (status & IMX7D_REG_ADC_INT_STATUS_CHANNEL_CONV_TIME_OUT) {
		dev_err(info->dev,
			"ADC got conversion time out interrupt: 0x%08x\n",
			status);
		status &= ~IMX7D_REG_ADC_INT_STATUS_CHANNEL_CONV_TIME_OUT;
		writel(status, info->regs + IMX7D_REG_ADC_INT_STATUS);
	}

	return IRQ_HANDLED;
}
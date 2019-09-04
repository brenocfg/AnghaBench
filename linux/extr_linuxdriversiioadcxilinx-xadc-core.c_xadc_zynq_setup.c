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
struct xadc {unsigned int zynq_intmask; int /*<<< orphan*/  clk; } ;
struct platform_device {int dummy; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int XADC_ZYNQ_CFG_ENABLE ; 
 unsigned int XADC_ZYNQ_CFG_IGAP (unsigned int) ; 
 unsigned int XADC_ZYNQ_CFG_REDGE ; 
 unsigned int XADC_ZYNQ_CFG_TCKRATE_DIV16 ; 
 unsigned int XADC_ZYNQ_CFG_TCKRATE_DIV2 ; 
 unsigned int XADC_ZYNQ_CFG_TCKRATE_DIV4 ; 
 unsigned int XADC_ZYNQ_CFG_TCKRATE_DIV8 ; 
 unsigned int XADC_ZYNQ_CFG_WEDGE ; 
 unsigned int XADC_ZYNQ_CTL_RESET ; 
 unsigned int XADC_ZYNQ_IGAP_DEFAULT ; 
 unsigned long XADC_ZYNQ_PCAP_RATE_MAX ; 
 int /*<<< orphan*/  XADC_ZYNQ_REG_CFG ; 
 int /*<<< orphan*/  XADC_ZYNQ_REG_CTL ; 
 int /*<<< orphan*/  XADC_ZYNQ_REG_INTMSK ; 
 int /*<<< orphan*/  XADC_ZYNQ_REG_INTSTS ; 
 unsigned long XADC_ZYNQ_TCK_RATE_MAX ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 struct xadc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  xadc_write_reg (struct xadc*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int xadc_zynq_setup(struct platform_device *pdev,
	struct iio_dev *indio_dev, int irq)
{
	struct xadc *xadc = iio_priv(indio_dev);
	unsigned long pcap_rate;
	unsigned int tck_div;
	unsigned int div;
	unsigned int igap;
	unsigned int tck_rate;
	int ret;

	/* TODO: Figure out how to make igap and tck_rate configurable */
	igap = XADC_ZYNQ_IGAP_DEFAULT;
	tck_rate = XADC_ZYNQ_TCK_RATE_MAX;

	xadc->zynq_intmask = ~0;

	pcap_rate = clk_get_rate(xadc->clk);
	if (!pcap_rate)
		return -EINVAL;

	if (pcap_rate > XADC_ZYNQ_PCAP_RATE_MAX) {
		ret = clk_set_rate(xadc->clk,
				   (unsigned long)XADC_ZYNQ_PCAP_RATE_MAX);
		if (ret)
			return ret;
	}

	if (tck_rate > pcap_rate / 2) {
		div = 2;
	} else {
		div = pcap_rate / tck_rate;
		if (pcap_rate / div > XADC_ZYNQ_TCK_RATE_MAX)
			div++;
	}

	if (div <= 3)
		tck_div = XADC_ZYNQ_CFG_TCKRATE_DIV2;
	else if (div <= 7)
		tck_div = XADC_ZYNQ_CFG_TCKRATE_DIV4;
	else if (div <= 15)
		tck_div = XADC_ZYNQ_CFG_TCKRATE_DIV8;
	else
		tck_div = XADC_ZYNQ_CFG_TCKRATE_DIV16;

	xadc_write_reg(xadc, XADC_ZYNQ_REG_CTL, XADC_ZYNQ_CTL_RESET);
	xadc_write_reg(xadc, XADC_ZYNQ_REG_CTL, 0);
	xadc_write_reg(xadc, XADC_ZYNQ_REG_INTSTS, ~0);
	xadc_write_reg(xadc, XADC_ZYNQ_REG_INTMSK, xadc->zynq_intmask);
	xadc_write_reg(xadc, XADC_ZYNQ_REG_CFG, XADC_ZYNQ_CFG_ENABLE |
			XADC_ZYNQ_CFG_REDGE | XADC_ZYNQ_CFG_WEDGE |
			tck_div | XADC_ZYNQ_CFG_IGAP(igap));

	if (pcap_rate > XADC_ZYNQ_PCAP_RATE_MAX) {
		ret = clk_set_rate(xadc->clk, pcap_rate);
		if (ret)
			return ret;
	}

	return 0;
}
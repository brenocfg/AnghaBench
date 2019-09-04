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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOMUX_TO_GPIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  MMC_PAD_CFG ; 
 int /*<<< orphan*/  MX31_PIN_GPIO1_1 ; 
 int /*<<< orphan*/  MX31_PIN_LCS0 ; 
 int /*<<< orphan*/  MX31_PIN_SD1_CLK ; 
 int /*<<< orphan*/  MX31_PIN_SD1_CMD ; 
 int /*<<< orphan*/  MX31_PIN_SD1_DATA0 ; 
 int /*<<< orphan*/  MX31_PIN_SD1_DATA1 ; 
 int /*<<< orphan*/  MX31_PIN_SD1_DATA2 ; 
 int /*<<< orphan*/  MX31_PIN_SD1_DATA3 ; 
 int /*<<< orphan*/  gpio_det ; 
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_wp ; 
 int /*<<< orphan*/  mxc_iomux_set_pad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 

__attribute__((used)) static int mxc_mmc1_init(struct device *dev,
			 irq_handler_t detect_irq, void *data)
{
	int ret;

	gpio_det = IOMUX_TO_GPIO(MX31_PIN_GPIO1_1);
	gpio_wp = IOMUX_TO_GPIO(MX31_PIN_LCS0);

	mxc_iomux_set_pad(MX31_PIN_SD1_DATA0, MMC_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_SD1_DATA1, MMC_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_SD1_DATA2, MMC_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_SD1_DATA3, MMC_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_SD1_CLK, MMC_PAD_CFG);
	mxc_iomux_set_pad(MX31_PIN_SD1_CMD, MMC_PAD_CFG);

	ret = gpio_request(gpio_det, "MMC detect");
	if (ret)
		return ret;

	ret = gpio_request(gpio_wp, "MMC w/p");
	if (ret)
		goto exit_free_det;

	gpio_direction_input(gpio_det);
	gpio_direction_input(gpio_wp);

	ret = request_irq(gpio_to_irq(IOMUX_TO_GPIO(MX31_PIN_GPIO1_1)),
			  detect_irq, IRQF_TRIGGER_FALLING,
			  "MMC detect", data);
	if (ret)
		goto exit_free_wp;

	return 0;

exit_free_wp:
	gpio_free(gpio_wp);

exit_free_det:
	gpio_free(gpio_det);

	return ret;
}
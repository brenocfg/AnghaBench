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
 int IOMUX_TO_GPIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  MX31_PIN_ATA_DMACK ; 
 int /*<<< orphan*/  MX31_PIN_ATA_RESET_B ; 
 int /*<<< orphan*/  gpio_direction_input (int) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 int gpio_request (int,char*) ; 
 int /*<<< orphan*/  gpio_to_irq (int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 

__attribute__((used)) static int armadillo5x0_sdhc1_init(struct device *dev,
				   irq_handler_t detect_irq, void *data)
{
	int ret;
	int gpio_det, gpio_wp;

	gpio_det = IOMUX_TO_GPIO(MX31_PIN_ATA_DMACK);
	gpio_wp = IOMUX_TO_GPIO(MX31_PIN_ATA_RESET_B);

	ret = gpio_request(gpio_det, "sdhc-card-detect");
	if (ret)
		return ret;

	gpio_direction_input(gpio_det);

	ret = gpio_request(gpio_wp, "sdhc-write-protect");
	if (ret)
		goto err_gpio_free;

	gpio_direction_input(gpio_wp);

	/* When supported the trigger type have to be BOTH */
	ret = request_irq(gpio_to_irq(IOMUX_TO_GPIO(MX31_PIN_ATA_DMACK)),
			  detect_irq, IRQF_TRIGGER_FALLING,
			  "sdhc-detect", data);

	if (ret)
		goto err_gpio_free_2;

	return 0;

err_gpio_free_2:
	gpio_free(gpio_wp);

err_gpio_free:
	gpio_free(gpio_det);

	return ret;

}
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
 int /*<<< orphan*/  IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  MX21ADS_IO_SD_WP ; 
 int /*<<< orphan*/  MX21ADS_MMC_CD ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 

__attribute__((used)) static int mx21ads_sdhc_init(struct device *dev, irq_handler_t detect_irq,
	void *data)
{
	int ret;

	ret = gpio_request(MX21ADS_IO_SD_WP, "mmc-ro");
	if (ret)
		return ret;

	return request_irq(gpio_to_irq(MX21ADS_MMC_CD), detect_irq,
			   IRQF_TRIGGER_FALLING, "mmc-detect", data);
}
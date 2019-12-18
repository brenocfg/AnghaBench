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
struct bmp280_data {int use_eoc; } ;

/* Variables and functions */
 unsigned long IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  bmp085_eoc_irq ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,char const*,struct bmp280_data*) ; 
 int /*<<< orphan*/  irq_get_irq_data (int) ; 
 unsigned long irqd_get_trigger_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bmp085_fetch_eoc_irq(struct device *dev,
				const char *name,
				int irq,
				struct bmp280_data *data)
{
	unsigned long irq_trig;
	int ret;

	irq_trig = irqd_get_trigger_type(irq_get_irq_data(irq));
	if (irq_trig != IRQF_TRIGGER_RISING) {
		dev_err(dev, "non-rising trigger given for EOC interrupt, "
			"trying to enforce it\n");
		irq_trig = IRQF_TRIGGER_RISING;
	}
	ret = devm_request_threaded_irq(dev,
			irq,
			bmp085_eoc_irq,
			NULL,
			irq_trig,
			name,
			data);
	if (ret) {
		/* Bail out without IRQ but keep the driver in place */
		dev_err(dev, "unable to request DRDY IRQ\n");
		return 0;
	}

	data->use_eoc = true;
	return 0;
}
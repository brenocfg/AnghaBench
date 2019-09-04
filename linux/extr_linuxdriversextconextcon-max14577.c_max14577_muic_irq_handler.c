#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct max14577_muic_info {int muic_irqs_num; int /*<<< orphan*/  irq_work; int /*<<< orphan*/  dev; TYPE_2__* max14577; TYPE_1__* muic_irqs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int dev_type; } ;
struct TYPE_3__ {int virq; int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
#define  MAXIM_DEVICE_TYPE_MAX14577 129 
#define  MAXIM_DEVICE_TYPE_MAX77836 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int max14577_parse_irq (struct max14577_muic_info*,int) ; 
 int max77836_parse_irq (struct max14577_muic_info*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t max14577_muic_irq_handler(int irq, void *data)
{
	struct max14577_muic_info *info = data;
	int i, irq_type = -1;
	bool irq_parsed;

	/*
	 * We may be called multiple times for different nested IRQ-s.
	 * Including changes in INT1_ADC and INT2_CGHTYP at once.
	 * However we only need to know whether it was ADC, charger
	 * or both interrupts so decode IRQ and turn on proper flags.
	 */
	for (i = 0; i < info->muic_irqs_num; i++)
		if (irq == info->muic_irqs[i].virq)
			irq_type = info->muic_irqs[i].irq;

	switch (info->max14577->dev_type) {
	case MAXIM_DEVICE_TYPE_MAX77836:
		irq_parsed = max77836_parse_irq(info, irq_type);
		break;
	case MAXIM_DEVICE_TYPE_MAX14577:
	default:
		irq_parsed = max14577_parse_irq(info, irq_type);
		break;
	}

	if (!irq_parsed) {
		dev_err(info->dev, "muic interrupt: irq %d occurred, skipped\n",
				irq_type);
		return IRQ_HANDLED;
	}
	schedule_work(&info->irq_work);

	return IRQ_HANDLED;
}
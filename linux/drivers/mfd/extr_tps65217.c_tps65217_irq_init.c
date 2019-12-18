#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tps65217 {int irq; TYPE_1__* dev; int /*<<< orphan*/  irq_domain; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  irq_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  TPS65217_INT_MASK ; 
 int /*<<< orphan*/  TPS65217_NUM_IRQ ; 
 int /*<<< orphan*/  TPS65217_PROTECT_NONE ; 
 int /*<<< orphan*/  TPS65217_REG_INT ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int devm_request_threaded_irq (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct tps65217*) ; 
 int /*<<< orphan*/  enable_irq_wake (int) ; 
 int /*<<< orphan*/  irq_domain_add_linear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct tps65217*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tps65217_irq_domain_ops ; 
 int /*<<< orphan*/  tps65217_irq_thread ; 
 int /*<<< orphan*/  tps65217_set_bits (struct tps65217*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65217_irq_init(struct tps65217 *tps, int irq)
{
	int ret;

	mutex_init(&tps->irq_lock);
	tps->irq = irq;

	/* Mask all interrupt sources */
	tps->irq_mask = TPS65217_INT_MASK;
	tps65217_set_bits(tps, TPS65217_REG_INT, TPS65217_INT_MASK,
			  TPS65217_INT_MASK, TPS65217_PROTECT_NONE);

	tps->irq_domain = irq_domain_add_linear(tps->dev->of_node,
		TPS65217_NUM_IRQ, &tps65217_irq_domain_ops, tps);
	if (!tps->irq_domain) {
		dev_err(tps->dev, "Could not create IRQ domain\n");
		return -ENOMEM;
	}

	ret = devm_request_threaded_irq(tps->dev, irq, NULL,
					tps65217_irq_thread, IRQF_ONESHOT,
					"tps65217-irq", tps);
	if (ret) {
		dev_err(tps->dev, "Failed to request IRQ %d: %d\n",
			irq, ret);
		return ret;
	}

	enable_irq_wake(irq);

	return 0;
}
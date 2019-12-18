#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lp8788_irq_data {int /*<<< orphan*/  irq_lock; scalar_t__ domain; struct lp8788* lp; } ;
struct lp8788 {int irq; TYPE_1__* dev; scalar_t__ irqdm; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  LP8788_INT_MAX ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,int) ; 
 struct lp8788_irq_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ irq_domain_add_linear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct lp8788_irq_data*) ; 
 int /*<<< orphan*/  lp8788_domain_ops ; 
 int /*<<< orphan*/  lp8788_irq_handler ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct lp8788_irq_data*) ; 

int lp8788_irq_init(struct lp8788 *lp, int irq)
{
	struct lp8788_irq_data *irqd;
	int ret;

	if (irq <= 0) {
		dev_warn(lp->dev, "invalid irq number: %d\n", irq);
		return 0;
	}

	irqd = devm_kzalloc(lp->dev, sizeof(*irqd), GFP_KERNEL);
	if (!irqd)
		return -ENOMEM;

	irqd->lp = lp;
	irqd->domain = irq_domain_add_linear(lp->dev->of_node, LP8788_INT_MAX,
					&lp8788_domain_ops, irqd);
	if (!irqd->domain) {
		dev_err(lp->dev, "failed to add irq domain err\n");
		return -EINVAL;
	}

	lp->irqdm = irqd->domain;
	mutex_init(&irqd->irq_lock);

	ret = request_threaded_irq(irq, NULL, lp8788_irq_handler,
				IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				"lp8788-irq", irqd);
	if (ret) {
		dev_err(lp->dev, "failed to create a thread for IRQ_N\n");
		return ret;
	}

	lp->irq = irq;

	return 0;
}
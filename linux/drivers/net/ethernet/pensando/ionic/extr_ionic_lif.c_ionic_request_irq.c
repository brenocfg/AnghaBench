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
struct ionic_queue {char* name; } ;
struct ionic_intr_info {int /*<<< orphan*/  name; int /*<<< orphan*/  vector; } ;
struct ionic_qcq {int /*<<< orphan*/  napi; struct ionic_queue q; struct ionic_intr_info intr; } ;
struct ionic_lif {TYPE_2__* netdev; scalar_t__ registered; TYPE_1__* ionic; } ;
struct device {int dummy; } ;
struct TYPE_4__ {char* name; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 char* IONIC_DRV_NAME ; 
 char* dev_name (struct device*) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ionic_isr ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char const*,char*) ; 

__attribute__((used)) static int ionic_request_irq(struct ionic_lif *lif, struct ionic_qcq *qcq)
{
	struct ionic_intr_info *intr = &qcq->intr;
	struct device *dev = lif->ionic->dev;
	struct ionic_queue *q = &qcq->q;
	const char *name;

	if (lif->registered)
		name = lif->netdev->name;
	else
		name = dev_name(dev);

	snprintf(intr->name, sizeof(intr->name),
		 "%s-%s-%s", IONIC_DRV_NAME, name, q->name);

	return devm_request_irq(dev, intr->vector, ionic_isr,
				0, intr->name, &qcq->napi);
}
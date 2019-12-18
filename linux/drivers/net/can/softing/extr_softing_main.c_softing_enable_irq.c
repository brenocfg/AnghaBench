#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int requested; int /*<<< orphan*/  nr; } ;
struct softing {TYPE_3__ irq; TYPE_2__* pdev; TYPE_1__* pdat; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct softing*) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct softing*) ; 
 int /*<<< orphan*/  softing_irq_thread ; 
 int /*<<< orphan*/  softing_irq_v1 ; 
 int /*<<< orphan*/  softing_irq_v2 ; 

int softing_enable_irq(struct softing *card, int enable)
{
	int ret;

	if (!card->irq.nr) {
		return 0;
	} else if (card->irq.requested && !enable) {
		free_irq(card->irq.nr, card);
		card->irq.requested = 0;
	} else if (!card->irq.requested && enable) {
		ret = request_threaded_irq(card->irq.nr,
				(card->pdat->generation >= 2) ?
					softing_irq_v2 : softing_irq_v1,
				softing_irq_thread, IRQF_SHARED,
				dev_name(&card->pdev->dev), card);
		if (ret) {
			dev_alert(&card->pdev->dev,
					"request_threaded_irq(%u) failed\n",
					card->irq.nr);
			return ret;
		}
		card->irq.requested = 1;
	}
	return 0;
}
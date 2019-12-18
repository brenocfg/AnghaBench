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
struct host1x {TYPE_3__* syncpt; TYPE_1__* info; int /*<<< orphan*/  intr_syncpt_irq; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  work; } ;
struct TYPE_6__ {TYPE_2__ intr; } ;
struct TYPE_4__ {unsigned int nb_pts; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct host1x*) ; 

__attribute__((used)) static int _host1x_free_syncpt_irq(struct host1x *host)
{
	unsigned int i;

	devm_free_irq(host->dev, host->intr_syncpt_irq, host);

	for (i = 0; i < host->info->nb_pts; i++)
		cancel_work_sync(&host->syncpt[i].intr.work);

	return 0;
}
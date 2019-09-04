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
typedef  scalar_t__ tegra_bpmp_mrq_handler_t ;
struct tegra_bpmp_mrq {unsigned int mrq; int /*<<< orphan*/  list; void* data; scalar_t__ handler; } ;
struct tegra_bpmp {int /*<<< orphan*/  lock; int /*<<< orphan*/  mrqs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct tegra_bpmp_mrq* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int tegra_bpmp_request_mrq(struct tegra_bpmp *bpmp, unsigned int mrq,
			   tegra_bpmp_mrq_handler_t handler, void *data)
{
	struct tegra_bpmp_mrq *entry;
	unsigned long flags;

	if (!handler)
		return -EINVAL;

	entry = devm_kzalloc(bpmp->dev, sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return -ENOMEM;

	spin_lock_irqsave(&bpmp->lock, flags);

	entry->mrq = mrq;
	entry->handler = handler;
	entry->data = data;
	list_add(&entry->list, &bpmp->mrqs);

	spin_unlock_irqrestore(&bpmp->lock, flags);

	return 0;
}
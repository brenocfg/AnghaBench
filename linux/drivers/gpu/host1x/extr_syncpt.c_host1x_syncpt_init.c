#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct host1x_syncpt_base {unsigned int id; } ;
struct host1x_syncpt {unsigned int id; struct host1x* host; } ;
struct host1x {int /*<<< orphan*/  nop_sp; struct host1x_syncpt_base* bases; struct host1x_syncpt* syncpt; int /*<<< orphan*/  syncpt_mutex; TYPE_1__* info; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {unsigned int nb_pts; unsigned int nb_bases; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* devm_kcalloc (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_hw_syncpt_assign_to_channel (struct host1x*,struct host1x_syncpt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host1x_hw_syncpt_enable_protection (struct host1x*) ; 
 int /*<<< orphan*/  host1x_syncpt_alloc (struct host1x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_syncpt_restore (struct host1x*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int host1x_syncpt_init(struct host1x *host)
{
	struct host1x_syncpt_base *bases;
	struct host1x_syncpt *syncpt;
	unsigned int i;

	syncpt = devm_kcalloc(host->dev, host->info->nb_pts, sizeof(*syncpt),
			      GFP_KERNEL);
	if (!syncpt)
		return -ENOMEM;

	bases = devm_kcalloc(host->dev, host->info->nb_bases, sizeof(*bases),
			     GFP_KERNEL);
	if (!bases)
		return -ENOMEM;

	for (i = 0; i < host->info->nb_pts; i++) {
		syncpt[i].id = i;
		syncpt[i].host = host;

		/*
		 * Unassign syncpt from channels for purposes of Tegra186
		 * syncpoint protection. This prevents any channel from
		 * accessing it until it is reassigned.
		 */
		host1x_hw_syncpt_assign_to_channel(host, &syncpt[i], NULL);
	}

	for (i = 0; i < host->info->nb_bases; i++)
		bases[i].id = i;

	mutex_init(&host->syncpt_mutex);
	host->syncpt = syncpt;
	host->bases = bases;

	host1x_syncpt_restore(host);
	host1x_hw_syncpt_enable_protection(host);

	/* Allocate sync point to use for clearing waits for expired fences */
	host->nop_sp = host1x_syncpt_alloc(host, NULL, 0);
	if (!host->nop_sp)
		return -ENOMEM;

	return 0;
}
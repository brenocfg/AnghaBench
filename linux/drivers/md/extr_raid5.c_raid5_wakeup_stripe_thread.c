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
struct stripe_head {int cpu; struct r5worker_group* group; int /*<<< orphan*/  lru; struct r5conf* raid_conf; } ;
struct r5worker_group {int stripes_cnt; TYPE_2__* workers; int /*<<< orphan*/  handle_list; int /*<<< orphan*/  loprio_list; } ;
struct r5conf {int worker_cnt_per_group; struct r5worker_group* worker_groups; TYPE_1__* mddev; } ;
struct TYPE_4__ {int working; int /*<<< orphan*/  work; } ;
struct TYPE_3__ {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int MAX_STRIPE_BATCH ; 
 int /*<<< orphan*/  cpu_online (int) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int cpu_to_group (int) ; 
 int cpumask_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work_on (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raid5_wq ; 
 scalar_t__ stripe_is_lowprio (struct stripe_head*) ; 

__attribute__((used)) static void raid5_wakeup_stripe_thread(struct stripe_head *sh)
{
	struct r5conf *conf = sh->raid_conf;
	struct r5worker_group *group;
	int thread_cnt;
	int i, cpu = sh->cpu;

	if (!cpu_online(cpu)) {
		cpu = cpumask_any(cpu_online_mask);
		sh->cpu = cpu;
	}

	if (list_empty(&sh->lru)) {
		struct r5worker_group *group;
		group = conf->worker_groups + cpu_to_group(cpu);
		if (stripe_is_lowprio(sh))
			list_add_tail(&sh->lru, &group->loprio_list);
		else
			list_add_tail(&sh->lru, &group->handle_list);
		group->stripes_cnt++;
		sh->group = group;
	}

	if (conf->worker_cnt_per_group == 0) {
		md_wakeup_thread(conf->mddev->thread);
		return;
	}

	group = conf->worker_groups + cpu_to_group(sh->cpu);

	group->workers[0].working = true;
	/* at least one worker should run to avoid race */
	queue_work_on(sh->cpu, raid5_wq, &group->workers[0].work);

	thread_cnt = group->stripes_cnt / MAX_STRIPE_BATCH - 1;
	/* wakeup more workers */
	for (i = 1; i < conf->worker_cnt_per_group && thread_cnt > 0; i++) {
		if (group->workers[i].working == false) {
			group->workers[i].working = true;
			queue_work_on(sh->cpu, raid5_wq,
				      &group->workers[i].work);
			thread_cnt--;
		}
	}
}
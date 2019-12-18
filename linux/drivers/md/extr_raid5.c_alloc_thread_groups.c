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
struct r5worker_group {int /*<<< orphan*/ * temp_inactive_list; int /*<<< orphan*/  work; struct r5worker_group* group; struct r5worker_group* workers; struct r5conf* conf; int /*<<< orphan*/  loprio_list; int /*<<< orphan*/  handle_list; } ;
struct r5worker {int /*<<< orphan*/ * temp_inactive_list; int /*<<< orphan*/  work; struct r5worker* group; struct r5worker* workers; struct r5conf* conf; int /*<<< orphan*/  loprio_list; int /*<<< orphan*/  handle_list; } ;
struct r5conf {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NR_STRIPE_HASH_LOCKS ; 
 struct r5worker_group* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct r5worker_group*) ; 
 int num_possible_nodes () ; 
 int /*<<< orphan*/  raid5_do_work ; 

__attribute__((used)) static int alloc_thread_groups(struct r5conf *conf, int cnt,
			       int *group_cnt,
			       int *worker_cnt_per_group,
			       struct r5worker_group **worker_groups)
{
	int i, j, k;
	ssize_t size;
	struct r5worker *workers;

	*worker_cnt_per_group = cnt;
	if (cnt == 0) {
		*group_cnt = 0;
		*worker_groups = NULL;
		return 0;
	}
	*group_cnt = num_possible_nodes();
	size = sizeof(struct r5worker) * cnt;
	workers = kcalloc(size, *group_cnt, GFP_NOIO);
	*worker_groups = kcalloc(*group_cnt, sizeof(struct r5worker_group),
				 GFP_NOIO);
	if (!*worker_groups || !workers) {
		kfree(workers);
		kfree(*worker_groups);
		return -ENOMEM;
	}

	for (i = 0; i < *group_cnt; i++) {
		struct r5worker_group *group;

		group = &(*worker_groups)[i];
		INIT_LIST_HEAD(&group->handle_list);
		INIT_LIST_HEAD(&group->loprio_list);
		group->conf = conf;
		group->workers = workers + i * cnt;

		for (j = 0; j < cnt; j++) {
			struct r5worker *worker = group->workers + j;
			worker->group = group;
			INIT_WORK(&worker->work, raid5_do_work);

			for (k = 0; k < NR_STRIPE_HASH_LOCKS; k++)
				INIT_LIST_HEAD(worker->temp_inactive_list + k);
		}
	}

	return 0;
}
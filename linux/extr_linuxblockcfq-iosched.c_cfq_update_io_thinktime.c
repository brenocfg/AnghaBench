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
struct cfq_queue {TYPE_1__* service_tree; } ;
struct cfq_io_cq {int /*<<< orphan*/  ttime; } ;
struct cfq_data {int /*<<< orphan*/  cfq_slice_idle; } ;
struct TYPE_2__ {int /*<<< orphan*/  ttime; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cfq_update_io_thinktime (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cfq_cfqq_sync (struct cfq_queue*) ; 

__attribute__((used)) static void
cfq_update_io_thinktime(struct cfq_data *cfqd, struct cfq_queue *cfqq,
			struct cfq_io_cq *cic)
{
	if (cfq_cfqq_sync(cfqq)) {
		__cfq_update_io_thinktime(&cic->ttime, cfqd->cfq_slice_idle);
		__cfq_update_io_thinktime(&cfqq->service_tree->ttime,
			cfqd->cfq_slice_idle);
	}
#ifdef CONFIG_CFQ_GROUP_IOSCHED
	__cfq_update_io_thinktime(&cfqq->cfqg->ttime, cfqd->cfq_group_idle);
#endif
}
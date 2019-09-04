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
struct sge {struct sched* tx_sched; } ;
struct sched {size_t port; TYPE_1__* p; int /*<<< orphan*/  sched_tsk; } ;
struct TYPE_2__ {int /*<<< orphan*/  skbq; } ;

/* Variables and functions */
 int MAX_NPORTS ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tx_sched_stop(struct sge *sge)
{
	struct sched *s = sge->tx_sched;
	int i;

	tasklet_kill(&s->sched_tsk);

	for (i = 0; i < MAX_NPORTS; i++)
		__skb_queue_purge(&s->p[s->port].skbq);
}
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
struct sched {TYPE_1__* p; int /*<<< orphan*/  sched_tsk; } ;
struct TYPE_2__ {int /*<<< orphan*/  skbq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_NPORTS ; 
 struct sched* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  restart_sched ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t1_sched_update_parms (struct sge*,int,int,int) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int tx_sched_init(struct sge *sge)
{
	struct sched *s;
	int i;

	s = kzalloc(sizeof (struct sched), GFP_KERNEL);
	if (!s)
		return -ENOMEM;

	pr_debug("tx_sched_init\n");
	tasklet_init(&s->sched_tsk, restart_sched, (unsigned long) sge);
	sge->tx_sched = s;

	for (i = 0; i < MAX_NPORTS; i++) {
		skb_queue_head_init(&s->p[i].skbq);
		t1_sched_update_parms(sge, i, 1500, 1000);
	}

	return 0;
}
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
struct mbox_chan {TYPE_1__* mbox; scalar_t__ con_priv; } ;
struct cmdq_thread {int /*<<< orphan*/  task_busy_list; scalar_t__ base; scalar_t__ atomic_exec; scalar_t__ priority; } ;
struct cmdq_task {int /*<<< orphan*/  list_entry; scalar_t__ pa_base; struct cmdq_pkt* pkt; struct cmdq_thread* thread; struct cmdq* cmdq; } ;
struct cmdq_pkt {scalar_t__ cmd_buf_size; scalar_t__ pa_base; } ;
struct cmdq {int suspended; int /*<<< orphan*/  clock; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long CMDQ_INST_SIZE ; 
 scalar_t__ CMDQ_THR_CURR_ADDR ; 
 scalar_t__ CMDQ_THR_ENABLED ; 
 scalar_t__ CMDQ_THR_ENABLE_TASK ; 
 scalar_t__ CMDQ_THR_END_ADDR ; 
 scalar_t__ CMDQ_THR_IRQ_EN ; 
 scalar_t__ CMDQ_THR_IRQ_ENABLE ; 
 scalar_t__ CMDQ_THR_PRIORITY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_task_insert_into_thread (struct cmdq_task*) ; 
 int /*<<< orphan*/  cmdq_task_remove_wfe (struct cmdq_task*) ; 
 int /*<<< orphan*/  cmdq_thread_is_in_wfe (struct cmdq_thread*) ; 
 scalar_t__ cmdq_thread_reset (struct cmdq*,struct cmdq_thread*) ; 
 int /*<<< orphan*/  cmdq_thread_resume (struct cmdq_thread*) ; 
 scalar_t__ cmdq_thread_suspend (struct cmdq*,struct cmdq_thread*) ; 
 int /*<<< orphan*/  cmdq_thread_wait_end (struct cmdq_thread*,unsigned long) ; 
 struct cmdq* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct cmdq_task* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int cmdq_mbox_send_data(struct mbox_chan *chan, void *data)
{
	struct cmdq_pkt *pkt = (struct cmdq_pkt *)data;
	struct cmdq_thread *thread = (struct cmdq_thread *)chan->con_priv;
	struct cmdq *cmdq = dev_get_drvdata(chan->mbox->dev);
	struct cmdq_task *task;
	unsigned long curr_pa, end_pa;

	/* Client should not flush new tasks if suspended. */
	WARN_ON(cmdq->suspended);

	task = kzalloc(sizeof(*task), GFP_ATOMIC);
	if (!task)
		return -ENOMEM;

	task->cmdq = cmdq;
	INIT_LIST_HEAD(&task->list_entry);
	task->pa_base = pkt->pa_base;
	task->thread = thread;
	task->pkt = pkt;

	if (list_empty(&thread->task_busy_list)) {
		WARN_ON(clk_enable(cmdq->clock) < 0);
		WARN_ON(cmdq_thread_reset(cmdq, thread) < 0);

		writel(task->pa_base, thread->base + CMDQ_THR_CURR_ADDR);
		writel(task->pa_base + pkt->cmd_buf_size,
		       thread->base + CMDQ_THR_END_ADDR);
		writel(thread->priority, thread->base + CMDQ_THR_PRIORITY);
		writel(CMDQ_THR_IRQ_EN, thread->base + CMDQ_THR_IRQ_ENABLE);
		writel(CMDQ_THR_ENABLED, thread->base + CMDQ_THR_ENABLE_TASK);
	} else {
		WARN_ON(cmdq_thread_suspend(cmdq, thread) < 0);
		curr_pa = readl(thread->base + CMDQ_THR_CURR_ADDR);
		end_pa = readl(thread->base + CMDQ_THR_END_ADDR);

		/*
		 * Atomic execution should remove the following wfe, i.e. only
		 * wait event at first task, and prevent to pause when running.
		 */
		if (thread->atomic_exec) {
			/* GCE is executing if command is not WFE */
			if (!cmdq_thread_is_in_wfe(thread)) {
				cmdq_thread_resume(thread);
				cmdq_thread_wait_end(thread, end_pa);
				WARN_ON(cmdq_thread_suspend(cmdq, thread) < 0);
				/* set to this task directly */
				writel(task->pa_base,
				       thread->base + CMDQ_THR_CURR_ADDR);
			} else {
				cmdq_task_insert_into_thread(task);
				cmdq_task_remove_wfe(task);
				smp_mb(); /* modify jump before enable thread */
			}
		} else {
			/* check boundary */
			if (curr_pa == end_pa - CMDQ_INST_SIZE ||
			    curr_pa == end_pa) {
				/* set to this task directly */
				writel(task->pa_base,
				       thread->base + CMDQ_THR_CURR_ADDR);
			} else {
				cmdq_task_insert_into_thread(task);
				smp_mb(); /* modify jump before enable thread */
			}
		}
		writel(task->pa_base + pkt->cmd_buf_size,
		       thread->base + CMDQ_THR_END_ADDR);
		cmdq_thread_resume(thread);
	}
	list_move_tail(&task->list_entry, &thread->task_busy_list);

	return 0;
}
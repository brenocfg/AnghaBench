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
struct sec_queue {scalar_t__ regs; scalar_t__ expected; int /*<<< orphan*/  task_irq; } ;

/* Variables and functions */
 scalar_t__ SEC_QUEUE_ENB_REG ; 
 int SEC_Q_INIT_AND_STAT_CLEAR ; 
 scalar_t__ SEC_Q_INIT_REG ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_queue_irq_enable (struct sec_queue*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void sec_queue_start(struct sec_queue *queue)
{
	sec_queue_irq_enable(queue);
	enable_irq(queue->task_irq);
	queue->expected = 0;
	writel_relaxed(SEC_Q_INIT_AND_STAT_CLEAR, queue->regs + SEC_Q_INIT_REG);
	writel_relaxed(0x1, queue->regs + SEC_QUEUE_ENB_REG);
}
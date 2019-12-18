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
struct cmdq_thread {scalar_t__ base; } ;
struct cmdq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMDQ_THR_DISABLED ; 
 scalar_t__ CMDQ_THR_ENABLE_TASK ; 
 int /*<<< orphan*/  cmdq_thread_reset (struct cmdq*,struct cmdq_thread*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cmdq_thread_disable(struct cmdq *cmdq, struct cmdq_thread *thread)
{
	cmdq_thread_reset(cmdq, thread);
	writel(CMDQ_THR_DISABLED, thread->base + CMDQ_THR_ENABLE_TASK);
}
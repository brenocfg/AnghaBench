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

/* Variables and functions */
 int CMDQ_THR_IS_WAITING ; 
 scalar_t__ CMDQ_THR_WAIT_TOKEN ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static bool cmdq_thread_is_in_wfe(struct cmdq_thread *thread)
{
	return readl(thread->base + CMDQ_THR_WAIT_TOKEN) & CMDQ_THR_IS_WAITING;
}
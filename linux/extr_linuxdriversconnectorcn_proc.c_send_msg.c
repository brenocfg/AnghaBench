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
struct proc_event {int /*<<< orphan*/  cpu; } ;
struct cn_msg {scalar_t__ data; scalar_t__ seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN_IDX_PROC ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 scalar_t__ __this_cpu_inc_return (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cn_netlink_send (struct cn_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  proc_event_counts ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static inline void send_msg(struct cn_msg *msg)
{
	preempt_disable();

	msg->seq = __this_cpu_inc_return(proc_event_counts) - 1;
	((struct proc_event *)msg->data)->cpu = smp_processor_id();

	/*
	 * Preemption remains disabled during send to ensure the messages are
	 * ordered according to their sequence numbers.
	 *
	 * If cn_netlink_send() fails, the data is not sent.
	 */
	cn_netlink_send(msg, 0, CN_IDX_PROC, GFP_NOWAIT);

	preempt_enable();
}
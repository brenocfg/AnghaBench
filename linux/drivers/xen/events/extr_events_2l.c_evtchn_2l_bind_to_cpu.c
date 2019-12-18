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
struct irq_info {unsigned int cpu; int /*<<< orphan*/  evtchn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_evtchn_mask ; 
 int /*<<< orphan*/  per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void evtchn_2l_bind_to_cpu(struct irq_info *info, unsigned cpu)
{
	clear_bit(info->evtchn, BM(per_cpu(cpu_evtchn_mask, info->cpu)));
	set_bit(info->evtchn, BM(per_cpu(cpu_evtchn_mask, cpu)));
}
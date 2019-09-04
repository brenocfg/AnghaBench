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
struct spu_queue {int /*<<< orphan*/  sharing; } ;
struct spu_qreg {unsigned long type; struct spu_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_online_mask ; 
 int cpumask_any_and (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spu_queue_register_workfn ; 
 int work_on_cpu_safe (int,int /*<<< orphan*/ ,struct spu_qreg*) ; 

__attribute__((used)) static int spu_queue_register(struct spu_queue *p, unsigned long q_type)
{
	int cpu = cpumask_any_and(&p->sharing, cpu_online_mask);
	struct spu_qreg qr = { .queue = p, .type = q_type };

	return work_on_cpu_safe(cpu, spu_queue_register_workfn, &qr);
}
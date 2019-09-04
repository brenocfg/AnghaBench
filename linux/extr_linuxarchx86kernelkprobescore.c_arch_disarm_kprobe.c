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
struct kprobe {int /*<<< orphan*/  opcode; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  text_poke (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void arch_disarm_kprobe(struct kprobe *p)
{
	text_poke(p->addr, &p->opcode, 1);
}
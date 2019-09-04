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
struct kprobe {scalar_t__ addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  copy_instruction (struct kprobe*) ; 
 scalar_t__ probe_is_prohibited_opcode (scalar_t__) ; 
 scalar_t__ s390_get_insn_slot (struct kprobe*) ; 

int arch_prepare_kprobe(struct kprobe *p)
{
	if ((unsigned long) p->addr & 0x01)
		return -EINVAL;
	/* Make sure the probe isn't going on a difficult instruction */
	if (probe_is_prohibited_opcode(p->addr))
		return -EINVAL;
	if (s390_get_insn_slot(p))
		return -ENOMEM;
	copy_instruction(p);
	return 0;
}
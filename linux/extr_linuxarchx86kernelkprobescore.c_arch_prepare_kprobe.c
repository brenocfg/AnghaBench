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
struct TYPE_2__ {int /*<<< orphan*/ * insn; } ;
struct kprobe {TYPE_1__ ainsn; scalar_t__ addr; } ;

/* Variables and functions */
 int EILSEQ ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ alternatives_text_reserved (scalar_t__,scalar_t__) ; 
 int arch_copy_kprobe (struct kprobe*) ; 
 int /*<<< orphan*/  can_probe (unsigned long) ; 
 int /*<<< orphan*/  free_insn_slot (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_insn_slot () ; 

int arch_prepare_kprobe(struct kprobe *p)
{
	int ret;

	if (alternatives_text_reserved(p->addr, p->addr))
		return -EINVAL;

	if (!can_probe((unsigned long)p->addr))
		return -EILSEQ;
	/* insn: must be on special executable page on x86. */
	p->ainsn.insn = get_insn_slot();
	if (!p->ainsn.insn)
		return -ENOMEM;

	ret = arch_copy_kprobe(p);
	if (ret) {
		free_insn_slot(p->ainsn.insn, 0);
		p->ainsn.insn = NULL;
	}

	return ret;
}
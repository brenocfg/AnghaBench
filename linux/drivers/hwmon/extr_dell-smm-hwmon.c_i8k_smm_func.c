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
struct smm_regs {int eax; int ebx; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int,unsigned long) ; 
 scalar_t__ smp_processor_id () ; 

__attribute__((used)) static int i8k_smm_func(void *par)
{
	int rc;
	struct smm_regs *regs = par;
	int eax = regs->eax;

#ifdef DEBUG
	int ebx = regs->ebx;
	unsigned long duration;
	ktime_t calltime, delta, rettime;

	calltime = ktime_get();
#endif

	/* SMM requires CPU 0 */
	if (smp_processor_id() != 0)
		return -EBUSY;

#if defined(CONFIG_X86_64)
	asm volatile("pushq %%rax\n\t"
		"movl 0(%%rax),%%edx\n\t"
		"pushq %%rdx\n\t"
		"movl 4(%%rax),%%ebx\n\t"
		"movl 8(%%rax),%%ecx\n\t"
		"movl 12(%%rax),%%edx\n\t"
		"movl 16(%%rax),%%esi\n\t"
		"movl 20(%%rax),%%edi\n\t"
		"popq %%rax\n\t"
		"out %%al,$0xb2\n\t"
		"out %%al,$0x84\n\t"
		"xchgq %%rax,(%%rsp)\n\t"
		"movl %%ebx,4(%%rax)\n\t"
		"movl %%ecx,8(%%rax)\n\t"
		"movl %%edx,12(%%rax)\n\t"
		"movl %%esi,16(%%rax)\n\t"
		"movl %%edi,20(%%rax)\n\t"
		"popq %%rdx\n\t"
		"movl %%edx,0(%%rax)\n\t"
		"pushfq\n\t"
		"popq %%rax\n\t"
		"andl $1,%%eax\n"
		: "=a"(rc)
		:    "a"(regs)
		:    "%ebx", "%ecx", "%edx", "%esi", "%edi", "memory");
#else
	asm volatile("pushl %%eax\n\t"
	    "movl 0(%%eax),%%edx\n\t"
	    "push %%edx\n\t"
	    "movl 4(%%eax),%%ebx\n\t"
	    "movl 8(%%eax),%%ecx\n\t"
	    "movl 12(%%eax),%%edx\n\t"
	    "movl 16(%%eax),%%esi\n\t"
	    "movl 20(%%eax),%%edi\n\t"
	    "popl %%eax\n\t"
	    "out %%al,$0xb2\n\t"
	    "out %%al,$0x84\n\t"
	    "xchgl %%eax,(%%esp)\n\t"
	    "movl %%ebx,4(%%eax)\n\t"
	    "movl %%ecx,8(%%eax)\n\t"
	    "movl %%edx,12(%%eax)\n\t"
	    "movl %%esi,16(%%eax)\n\t"
	    "movl %%edi,20(%%eax)\n\t"
	    "popl %%edx\n\t"
	    "movl %%edx,0(%%eax)\n\t"
	    "lahf\n\t"
	    "shrl $8,%%eax\n\t"
	    "andl $1,%%eax\n"
	    : "=a"(rc)
	    :    "a"(regs)
	    :    "%ebx", "%ecx", "%edx", "%esi", "%edi", "memory");
#endif
	if (rc != 0 || (regs->eax & 0xffff) == 0xffff || regs->eax == eax)
		rc = -EINVAL;

#ifdef DEBUG
	rettime = ktime_get();
	delta = ktime_sub(rettime, calltime);
	duration = ktime_to_ns(delta) >> 10;
	pr_debug("smm(0x%.4x 0x%.4x) = 0x%.4x  (took %7lu usecs)\n", eax, ebx,
		(rc ? 0xffff : regs->eax & 0xffff), duration);
#endif

	return rc;
}
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
struct pt_regs {unsigned long sp; } ;
struct ksignal {int dummy; } ;

/* Variables and functions */
 unsigned long sigsp (unsigned long,struct ksignal*) ; 

__attribute__((used)) static inline void *get_sigframe(struct ksignal *ksig, struct pt_regs *regs,
				 size_t frame_size)
{
	unsigned long usp;

	/* Default to using normal stack.  */
	usp = regs->sp;

	/* This is the X/Open sanctioned signal stack switching.  */
	usp = sigsp(usp, ksig);

	/* Verify, is it 32 or 64 bit aligned */
	return (void *)((usp - frame_size) & -8UL);
}
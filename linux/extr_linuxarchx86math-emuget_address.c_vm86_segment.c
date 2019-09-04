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
typedef  int /*<<< orphan*/  u_char ;
struct address {scalar_t__ selector; } ;

/* Variables and functions */
 scalar_t__ VM86_REG_ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long vm86_segment(u_char segment, struct address *addr)
{
	segment--;
#ifdef PARANOID
	if (segment > PREFIX_SS_) {
		EXCEPTION(EX_INTERNAL | 0x130);
		math_abort(FPU_info, SIGSEGV);
	}
#endif /* PARANOID */
	addr->selector = VM86_REG_(segment);
	return (unsigned long)VM86_REG_(segment) << 4;
}
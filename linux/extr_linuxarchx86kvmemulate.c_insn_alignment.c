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
typedef  int u64 ;
struct x86_emulate_ctxt {int d; } ;

/* Variables and functions */
 int AlignMask ; 
#define  Aligned 131 
#define  Aligned16 130 
#define  Avx 129 
#define  Unaligned 128 
 scalar_t__ likely (int) ; 

__attribute__((used)) static unsigned insn_alignment(struct x86_emulate_ctxt *ctxt, unsigned size)
{
	u64 alignment = ctxt->d & AlignMask;

	if (likely(size < 16))
		return 1;

	switch (alignment) {
	case Unaligned:
	case Avx:
		return 1;
	case Aligned16:
		return 16;
	case Aligned:
	default:
		return size;
	}
}
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

/* Variables and functions */
 int /*<<< orphan*/  DART_CNTL ; 
 unsigned long DART_CNTL_U4_ENABLE ; 
 unsigned long DART_CNTL_U4_IONE ; 
 unsigned long DART_CNTL_U4_IONE_MASK ; 
 unsigned long DART_IN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DART_OUT (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  invalidate_lock ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void dart_tlb_invalidate_one(unsigned long bus_rpn)
{
	unsigned int reg;
	unsigned int l, limit;
	unsigned long flags;

	spin_lock_irqsave(&invalidate_lock, flags);

	reg = DART_CNTL_U4_ENABLE | DART_CNTL_U4_IONE |
		(bus_rpn & DART_CNTL_U4_IONE_MASK);
	DART_OUT(DART_CNTL, reg);

	limit = 0;
wait_more:
	l = 0;
	while ((DART_IN(DART_CNTL) & DART_CNTL_U4_IONE) && l < (1L << limit)) {
		rmb();
		l++;
	}

	if (l == (1L << limit)) {
		if (limit < 4) {
			limit++;
			goto wait_more;
		} else
			panic("DART: TLB did not flush after waiting a long "
			      "time. Buggy U4 ?");
	}

	spin_unlock_irqrestore(&invalidate_lock, flags);
}
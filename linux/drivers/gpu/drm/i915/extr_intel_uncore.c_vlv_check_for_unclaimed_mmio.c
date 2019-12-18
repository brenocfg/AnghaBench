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
typedef  int u32 ;
struct intel_uncore {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAIM_ER ; 
 int /*<<< orphan*/  CLAIM_ER_CLR ; 
 int CLAIM_ER_CTR_MASK ; 
 int CLAIM_ER_OVERFLOW ; 
 int __raw_uncore_read32 (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_uncore_write32 (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static bool
vlv_check_for_unclaimed_mmio(struct intel_uncore *uncore)
{
	u32 cer;

	cer = __raw_uncore_read32(uncore, CLAIM_ER);
	if (likely(!(cer & (CLAIM_ER_OVERFLOW | CLAIM_ER_CTR_MASK))))
		return false;

	__raw_uncore_write32(uncore, CLAIM_ER, CLAIM_ER_CLR);

	return true;
}
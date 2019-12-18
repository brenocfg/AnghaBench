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
typedef  int /*<<< orphan*/  u32 ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool is_pmu_set(struct ath_hw *ah, u32 pmu_reg, int pmu_set)
{
	int timeout = 100;

	while (pmu_set != REG_READ(ah, pmu_reg)) {
		if (timeout-- == 0)
			return false;
		REG_WRITE(ah, pmu_reg, pmu_set);
		udelay(10);
	}

	return true;
}
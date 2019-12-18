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
struct intel_uncore {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN6_GT_THREAD_STATUS_CORE_MASK ; 
 int /*<<< orphan*/  GEN6_GT_THREAD_STATUS_REG ; 
 int /*<<< orphan*/  __raw_uncore_read32 (struct intel_uncore*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 gt_thread_status(struct intel_uncore *uncore)
{
	u32 val;

	val = __raw_uncore_read32(uncore, GEN6_GT_THREAD_STATUS_REG);
	val &= GEN6_GT_THREAD_STATUS_CORE_MASK;

	return val;
}
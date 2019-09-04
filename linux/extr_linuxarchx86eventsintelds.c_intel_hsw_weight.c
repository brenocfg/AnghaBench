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
union hsw_tsx_tuning {int /*<<< orphan*/  cycles_last_block; scalar_t__ value; } ;
typedef  int /*<<< orphan*/  u64 ;
struct pebs_record_skl {scalar_t__ tsx_tuning; } ;

/* Variables and functions */

__attribute__((used)) static inline u64 intel_hsw_weight(struct pebs_record_skl *pebs)
{
	if (pebs->tsx_tuning) {
		union hsw_tsx_tuning tsx = { .value = pebs->tsx_tuning };
		return tsx.cycles_last_block;
	}
	return 0;
}
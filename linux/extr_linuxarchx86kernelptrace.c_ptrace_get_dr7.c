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
struct TYPE_2__ {int /*<<< orphan*/  disabled; } ;
struct perf_event {TYPE_1__ attr; } ;
struct arch_hw_breakpoint {int /*<<< orphan*/  type; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int HBP_NUM ; 
 struct arch_hw_breakpoint* counter_arch_bp (struct perf_event*) ; 
 int encode_dr7 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long ptrace_get_dr7(struct perf_event *bp[])
{
	int i;
	int dr7 = 0;
	struct arch_hw_breakpoint *info;

	for (i = 0; i < HBP_NUM; i++) {
		if (bp[i] && !bp[i]->attr.disabled) {
			info = counter_arch_bp(bp[i]);
			dr7 |= encode_dr7(i, info->len, info->type);
		}
	}

	return dr7;
}
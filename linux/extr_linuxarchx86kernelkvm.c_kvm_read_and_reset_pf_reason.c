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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  reason; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 scalar_t__ __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ apf_reason ; 

u32 kvm_read_and_reset_pf_reason(void)
{
	u32 reason = 0;

	if (__this_cpu_read(apf_reason.enabled)) {
		reason = __this_cpu_read(apf_reason.reason);
		__this_cpu_write(apf_reason.reason, 0);
	}

	return reason;
}
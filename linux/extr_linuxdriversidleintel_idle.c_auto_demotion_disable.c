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
struct TYPE_2__ {unsigned long long auto_demotion_disable_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_PKG_CST_CONFIG_CONTROL ; 
 TYPE_1__* icpu ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void auto_demotion_disable(void)
{
	unsigned long long msr_bits;

	rdmsrl(MSR_PKG_CST_CONFIG_CONTROL, msr_bits);
	msr_bits &= ~(icpu->auto_demotion_disable_flags);
	wrmsrl(MSR_PKG_CST_CONFIG_CONTROL, msr_bits);
}
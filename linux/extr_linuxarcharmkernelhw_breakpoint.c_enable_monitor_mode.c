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

/* Variables and functions */
 int /*<<< orphan*/  ARM_DBG_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ARM_DBG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
#define  ARM_DEBUG_ARCH_V6 132 
#define  ARM_DEBUG_ARCH_V6_1 131 
#define  ARM_DEBUG_ARCH_V7_1 130 
#define  ARM_DEBUG_ARCH_V7_ECP14 129 
#define  ARM_DEBUG_ARCH_V8 128 
 int ARM_DSCR_MDBGEN ; 
 int ENODEV ; 
 int EPERM ; 
 int /*<<< orphan*/  c0 ; 
 int /*<<< orphan*/  c1 ; 
 int /*<<< orphan*/  c2 ; 
 int get_debug_arch () ; 
 int /*<<< orphan*/  isb () ; 
 int /*<<< orphan*/  pr_warn_once (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static int enable_monitor_mode(void)
{
	u32 dscr;
	ARM_DBG_READ(c0, c1, 0, dscr);

	/* If monitor mode is already enabled, just return. */
	if (dscr & ARM_DSCR_MDBGEN)
		goto out;

	/* Write to the corresponding DSCR. */
	switch (get_debug_arch()) {
	case ARM_DEBUG_ARCH_V6:
	case ARM_DEBUG_ARCH_V6_1:
		ARM_DBG_WRITE(c0, c1, 0, (dscr | ARM_DSCR_MDBGEN));
		break;
	case ARM_DEBUG_ARCH_V7_ECP14:
	case ARM_DEBUG_ARCH_V7_1:
	case ARM_DEBUG_ARCH_V8:
		ARM_DBG_WRITE(c0, c2, 2, (dscr | ARM_DSCR_MDBGEN));
		isb();
		break;
	default:
		return -ENODEV;
	}

	/* Check that the write made it through. */
	ARM_DBG_READ(c0, c1, 0, dscr);
	if (!(dscr & ARM_DSCR_MDBGEN)) {
		pr_warn_once("Failed to enable monitor mode on CPU %d.\n",
				smp_processor_id());
		return -EPERM;
	}

out:
	return 0;
}
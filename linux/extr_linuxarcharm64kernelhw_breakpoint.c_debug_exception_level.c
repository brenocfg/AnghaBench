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
typedef  enum dbg_active_el { ____Placeholder_dbg_active_el } dbg_active_el ;

/* Variables and functions */
#define  AARCH64_BREAKPOINT_EL0 129 
#define  AARCH64_BREAKPOINT_EL1 128 
 int DBG_ACTIVE_EL0 ; 
 int DBG_ACTIVE_EL1 ; 
 int EINVAL ; 
 int /*<<< orphan*/  pr_warning (char*,int) ; 

__attribute__((used)) static enum dbg_active_el debug_exception_level(int privilege)
{
	switch (privilege) {
	case AARCH64_BREAKPOINT_EL0:
		return DBG_ACTIVE_EL0;
	case AARCH64_BREAKPOINT_EL1:
		return DBG_ACTIVE_EL1;
	default:
		pr_warning("invalid breakpoint privilege level %d\n", privilege);
		return -EINVAL;
	}
}
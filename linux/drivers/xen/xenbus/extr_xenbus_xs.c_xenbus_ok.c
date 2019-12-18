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
#define  SYSTEM_HALT 133 
#define  SYSTEM_POWER_OFF 132 
#define  SYSTEM_RESTART 131 
#define  XS_HVM 130 
#define  XS_LOCAL 129 
#define  XS_PV 128 
 int /*<<< orphan*/  system_state ; 
 int xen_store_domain_type ; 

__attribute__((used)) static bool xenbus_ok(void)
{
	switch (xen_store_domain_type) {
	case XS_LOCAL:
		switch (system_state) {
		case SYSTEM_POWER_OFF:
		case SYSTEM_RESTART:
		case SYSTEM_HALT:
			return false;
		default:
			break;
		}
		return true;
	case XS_PV:
	case XS_HVM:
		/* FIXME: Could check that the remote domain is alive,
		 * but it is normally initial domain. */
		return true;
	default:
		break;
	}
	return false;
}
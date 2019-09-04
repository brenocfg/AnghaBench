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
 int /*<<< orphan*/  HYPERVISOR_xen_version (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void xen_force_evtchn_callback(void)
{
	(void)HYPERVISOR_xen_version(0, NULL);
}
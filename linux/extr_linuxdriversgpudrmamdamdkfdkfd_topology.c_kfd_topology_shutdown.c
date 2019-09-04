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
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfd_release_live_view () ; 
 int /*<<< orphan*/  kfd_topology_release_sysfs () ; 
 int /*<<< orphan*/  topology_lock ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void kfd_topology_shutdown(void)
{
	down_write(&topology_lock);
	kfd_topology_release_sysfs();
	kfd_release_live_view();
	up_write(&topology_lock);
}
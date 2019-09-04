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
 int EBUSY ; 
 int /*<<< orphan*/  ap_wfs_count ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int num_online_cpus () ; 
 scalar_t__ tboot_wait_for_aps (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tboot_dying_cpu(unsigned int cpu)
{
	atomic_inc(&ap_wfs_count);
	if (num_online_cpus() == 1) {
		if (tboot_wait_for_aps(atomic_read(&ap_wfs_count)))
			return -EBUSY;
	}
	return 0;
}
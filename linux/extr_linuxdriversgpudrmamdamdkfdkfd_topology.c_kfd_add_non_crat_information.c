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
struct kfd_topology_device {int /*<<< orphan*/  gpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmi_walk (int /*<<< orphan*/ ,struct kfd_topology_device*) ; 
 int /*<<< orphan*/  find_system_memory ; 

__attribute__((used)) static void kfd_add_non_crat_information(struct kfd_topology_device *kdev)
{
	/* Check if CPU only node. */
	if (!kdev->gpu) {
		/* Add system memory information */
		dmi_walk(find_system_memory, kdev);
	}
	/* TODO: For GPU node, rearrange code from kfd_topology_add_device */
}
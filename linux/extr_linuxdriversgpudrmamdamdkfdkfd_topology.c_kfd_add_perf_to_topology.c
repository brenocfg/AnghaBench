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
struct kfd_topology_device {int dummy; } ;

/* Variables and functions */
 int kfd_iommu_add_perf_counters (struct kfd_topology_device*) ; 

__attribute__((used)) static int kfd_add_perf_to_topology(struct kfd_topology_device *kdev)
{
	/* These are the only counters supported so far */
	return kfd_iommu_add_perf_counters(kdev);
}
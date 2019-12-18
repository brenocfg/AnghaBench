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
struct l2cache_pmu {int /*<<< orphan*/  pmu_cluster; } ;
struct cluster_pmu {int dummy; } ;

/* Variables and functions */
 struct cluster_pmu** per_cpu_ptr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline struct cluster_pmu *get_cluster_pmu(
	struct l2cache_pmu *l2cache_pmu, int cpu)
{
	return *per_cpu_ptr(l2cache_pmu->pmu_cluster, cpu);
}
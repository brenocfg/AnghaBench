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
struct iommu_table {scalar_t__ it_base; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 unsigned long be64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long tce_get_pseries(struct iommu_table *tbl, long index)
{
	__be64 *tcep;

	tcep = ((__be64 *)tbl->it_base) + index;

	return be64_to_cpu(*tcep);
}
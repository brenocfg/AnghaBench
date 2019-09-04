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
struct iommu_table {int dummy; } ;

/* Variables and functions */
 scalar_t__ dart_dirty ; 
 int /*<<< orphan*/  dart_tlb_invalidate_all () ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static void dart_flush(struct iommu_table *tbl)
{
	mb();
	if (dart_dirty) {
		dart_tlb_invalidate_all();
		dart_dirty = 0;
	}
}
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
struct gart_device {unsigned long iovmm_base; unsigned long page_count; } ;

/* Variables and functions */
 unsigned long GART_PAGE_SIZE ; 

__attribute__((used)) static inline bool gart_iova_range_valid(struct gart_device *gart,
					 unsigned long iova, size_t bytes)
{
	unsigned long iova_start, iova_end, gart_start, gart_end;

	iova_start = iova;
	iova_end = iova_start + bytes - 1;
	gart_start = gart->iovmm_base;
	gart_end = gart_start + gart->page_count * GART_PAGE_SIZE - 1;

	if (iova_start < gart_start)
		return false;
	if (iova_end > gart_end)
		return false;
	return true;
}
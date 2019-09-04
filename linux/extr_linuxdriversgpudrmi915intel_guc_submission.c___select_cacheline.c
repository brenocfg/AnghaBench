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
struct intel_guc {int /*<<< orphan*/  db_cacheline; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,unsigned long,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ cache_line_size () ; 
 unsigned long offset_in_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long __select_cacheline(struct intel_guc *guc)
{
	unsigned long offset;

	/* Doorbell uses a single cache line within a page */
	offset = offset_in_page(guc->db_cacheline);

	/* Moving to next cache line to reduce contention */
	guc->db_cacheline += cache_line_size();

	DRM_DEBUG_DRIVER("reserved cacheline 0x%lx, next 0x%x, linesize %u\n",
			 offset, guc->db_cacheline, cache_line_size());
	return offset;
}
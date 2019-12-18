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
typedef  int u64 ;
struct cxl_context {int dummy; } ;

/* Variables and functions */
 int CXL_PSL_DSISR_An_DS ; 
 scalar_t__ cxl_is_power8 () ; 

__attribute__((used)) static bool cxl_is_segment_miss(struct cxl_context *ctx, u64 dsisr)
{
	if ((cxl_is_power8() && (dsisr & CXL_PSL_DSISR_An_DS)))
		return true;

	return false;
}
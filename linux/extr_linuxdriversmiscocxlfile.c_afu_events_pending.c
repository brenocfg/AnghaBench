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
struct ocxl_context {int dummy; } ;

/* Variables and functions */
 scalar_t__ has_xsl_error (struct ocxl_context*) ; 

__attribute__((used)) static bool afu_events_pending(struct ocxl_context *ctx)
{
	if (has_xsl_error(ctx))
		return true;
	return false;
}
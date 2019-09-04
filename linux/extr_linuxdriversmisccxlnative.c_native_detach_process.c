#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cxl_context {TYPE_1__* afu; } ;
struct TYPE_2__ {scalar_t__ current_mode; } ;

/* Variables and functions */
 scalar_t__ CXL_MODE_DEDICATED ; 
 int detach_process_native_afu_directed (struct cxl_context*) ; 
 int detach_process_native_dedicated (struct cxl_context*) ; 
 int /*<<< orphan*/  trace_cxl_detach (struct cxl_context*) ; 

__attribute__((used)) static int native_detach_process(struct cxl_context *ctx)
{
	trace_cxl_detach(ctx);

	if (ctx->afu->current_mode == CXL_MODE_DEDICATED)
		return detach_process_native_dedicated(ctx);

	return detach_process_native_afu_directed(ctx);
}
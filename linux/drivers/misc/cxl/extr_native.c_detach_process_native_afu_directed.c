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
struct cxl_context {int /*<<< orphan*/  pe_inserted; } ;

/* Variables and functions */
 scalar_t__ remove_process_element (struct cxl_context*) ; 
 scalar_t__ terminate_process_element (struct cxl_context*) ; 

__attribute__((used)) static inline int detach_process_native_afu_directed(struct cxl_context *ctx)
{
	if (!ctx->pe_inserted)
		return 0;
	if (terminate_process_element(ctx))
		return -1;
	if (remove_process_element(ctx))
		return -1;

	return 0;
}
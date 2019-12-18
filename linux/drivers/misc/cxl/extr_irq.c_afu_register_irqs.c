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
typedef  int /*<<< orphan*/  u32 ;
struct cxl_context {int dummy; } ;

/* Variables and functions */
 int afu_allocate_irqs (struct cxl_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afu_register_hwirqs (struct cxl_context*) ; 

int afu_register_irqs(struct cxl_context *ctx, u32 count)
{
	int rc;

	rc = afu_allocate_irqs(ctx, count);
	if (rc)
		return rc;

	afu_register_hwirqs(ctx);
	return 0;
}
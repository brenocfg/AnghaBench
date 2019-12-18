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
struct cxl_context {scalar_t__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmdrop (scalar_t__) ; 

void cxl_context_mm_count_put(struct cxl_context *ctx)
{
	if (ctx->mm)
		mmdrop(ctx->mm);
}
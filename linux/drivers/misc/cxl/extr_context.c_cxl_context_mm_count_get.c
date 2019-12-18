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
struct cxl_context {TYPE_1__* mm; } ;
struct TYPE_2__ {int /*<<< orphan*/  mm_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

void cxl_context_mm_count_get(struct cxl_context *ctx)
{
	if (ctx->mm)
		atomic_inc(&ctx->mm->mm_count);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cxl_context {int /*<<< orphan*/  process_token; TYPE_2__* afu; int /*<<< orphan*/  pe_inserted; } ;
struct TYPE_4__ {TYPE_1__* guest; } ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ cxl_h_detach_process (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int detach_afu_directed(struct cxl_context *ctx)
{
	if (!ctx->pe_inserted)
		return 0;
	if (cxl_h_detach_process(ctx->afu->guest->handle, ctx->process_token))
		return -1;
	return 0;
}
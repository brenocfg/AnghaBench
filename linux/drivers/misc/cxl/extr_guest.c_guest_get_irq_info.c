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
struct cxl_irq_info {int dummy; } ;
struct cxl_context {int /*<<< orphan*/  process_token; TYPE_2__* afu; } ;
struct TYPE_4__ {TYPE_1__* guest; } ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int cxl_h_collect_int_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cxl_irq_info*) ; 

__attribute__((used)) static int guest_get_irq_info(struct cxl_context *ctx, struct cxl_irq_info *info)
{
	return cxl_h_collect_int_info(ctx->afu->guest->handle, ctx->process_token, info);
}
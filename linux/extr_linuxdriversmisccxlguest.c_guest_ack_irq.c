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
typedef  int u64 ;
struct cxl_context {int /*<<< orphan*/  process_token; TYPE_2__* afu; } ;
struct TYPE_4__ {TYPE_1__* guest; } ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int cxl_h_control_faults (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int guest_ack_irq(struct cxl_context *ctx, u64 tfc, u64 psl_reset_mask)
{
	return cxl_h_control_faults(ctx->afu->guest->handle, ctx->process_token,
				tfc >> 32, (psl_reset_mask != 0));
}
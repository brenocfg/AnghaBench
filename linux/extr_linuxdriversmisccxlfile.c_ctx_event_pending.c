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
struct cxl_context {int /*<<< orphan*/  afu_driver_events; scalar_t__ afu_driver_ops; scalar_t__ pending_afu_err; scalar_t__ pending_fault; scalar_t__ pending_irq; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool ctx_event_pending(struct cxl_context *ctx)
{
	if (ctx->pending_irq || ctx->pending_fault || ctx->pending_afu_err)
		return true;

	if (ctx->afu_driver_ops && atomic_read(&ctx->afu_driver_events))
		return true;

	return false;
}
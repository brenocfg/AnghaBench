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
struct cxl_context {int /*<<< orphan*/  wq; int /*<<< orphan*/  afu_driver_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void cxl_context_events_pending(struct cxl_context *ctx,
				unsigned int new_events)
{
	atomic_add(new_events, &ctx->afu_driver_events);
	wake_up_all(&ctx->wq);
}
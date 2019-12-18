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
struct urb {int status; struct queued_ctx* context; } ;
struct queued_ctx {int status; int num; int /*<<< orphan*/  complete; int /*<<< orphan*/  pending; struct urb** urbs; } ;

/* Variables and functions */
 int ECONNRESET ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unlink_queued_callback(struct urb *urb)
{
	int			status = urb->status;
	struct queued_ctx	*ctx = urb->context;

	if (ctx->status)
		goto done;
	if (urb == ctx->urbs[ctx->num - 4] || urb == ctx->urbs[ctx->num - 2]) {
		if (status == -ECONNRESET)
			goto done;
		/* What error should we report if the URB completed normally? */
	}
	if (status != 0)
		ctx->status = status;

 done:
	if (atomic_dec_and_test(&ctx->pending))
		complete(&ctx->complete);
}
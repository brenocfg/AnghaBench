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
struct urb {int /*<<< orphan*/  status; struct u2fzero_transfer_context* context; } ;
struct u2fzero_transfer_context {int /*<<< orphan*/  done; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void u2fzero_read_callback(struct urb *urb)
{
	struct u2fzero_transfer_context *ctx = urb->context;

	ctx->status = urb->status;
	complete(&ctx->done);
}
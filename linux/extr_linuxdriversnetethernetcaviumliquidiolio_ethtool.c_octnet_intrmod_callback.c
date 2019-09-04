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
struct octeon_soft_command {scalar_t__ ctxptr; } ;
struct octeon_device {int dummy; } ;
struct oct_intrmod_context {int /*<<< orphan*/  wc; int /*<<< orphan*/  cond; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void octnet_intrmod_callback(struct octeon_device *oct_dev,
				    u32 status,
				    void *ptr)
{
	struct octeon_soft_command *sc = (struct octeon_soft_command *)ptr;
	struct oct_intrmod_context *ctx;

	ctx  = (struct oct_intrmod_context *)sc->ctxptr;

	ctx->status = status;

	WRITE_ONCE(ctx->cond, 1);

	/* This barrier is required to be sure that the response has been
	 * written fully before waking up the handler
	 */
	wmb();

	wake_up_interruptible(&ctx->wc);
}
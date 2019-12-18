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
struct fimc_dev {int /*<<< orphan*/  irq_queue; } ;
struct fimc_ctx {struct fimc_dev* fimc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIMC_CTX_SHUT ; 
 int /*<<< orphan*/  FIMC_SHUTDOWN_TIMEOUT ; 
 int /*<<< orphan*/  fimc_ctx_state_is_set (int /*<<< orphan*/ ,struct fimc_ctx*) ; 
 int /*<<< orphan*/  fimc_ctx_state_set (int /*<<< orphan*/ ,struct fimc_ctx*) ; 
 int /*<<< orphan*/  fimc_m2m_pending (struct fimc_dev*) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimc_m2m_shutdown(struct fimc_ctx *ctx)
{
	struct fimc_dev *fimc = ctx->fimc_dev;

	if (!fimc_m2m_pending(fimc))
		return;

	fimc_ctx_state_set(FIMC_CTX_SHUT, ctx);

	wait_event_timeout(fimc->irq_queue,
			!fimc_ctx_state_is_set(FIMC_CTX_SHUT, ctx),
			FIMC_SHUTDOWN_TIMEOUT);
}
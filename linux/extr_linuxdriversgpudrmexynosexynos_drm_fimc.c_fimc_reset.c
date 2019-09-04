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
struct fimc_context {int /*<<< orphan*/  sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  fimc_clear_addr (struct fimc_context*) ; 
 int /*<<< orphan*/  fimc_sw_reset (struct fimc_context*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void fimc_reset(struct fimc_context *ctx)
{
	/* reset h/w block */
	fimc_sw_reset(ctx);

	/* reset scaler capability */
	memset(&ctx->sc, 0x0, sizeof(ctx->sc));

	fimc_clear_addr(ctx);
}
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
struct iser_pi_context {int /*<<< orphan*/  sig_mr; int /*<<< orphan*/  rsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dereg_mr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iser_free_reg_res (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct iser_pi_context*) ; 

__attribute__((used)) static void
iser_free_pi_ctx(struct iser_pi_context *pi_ctx)
{
	iser_free_reg_res(&pi_ctx->rsc);
	ib_dereg_mr(pi_ctx->sig_mr);
	kfree(pi_ctx);
}
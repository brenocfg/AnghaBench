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
typedef  int /*<<< orphan*/  u8 ;
struct at86rf230_state_change {void (* complete ) (void*) ;int /*<<< orphan*/  to_state; } ;
struct at86rf230_local {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RG_TRX_STATUS ; 
 int /*<<< orphan*/  at86rf230_async_read_reg (struct at86rf230_local*,int /*<<< orphan*/ ,struct at86rf230_state_change*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at86rf230_async_state_change_start ; 

__attribute__((used)) static void
at86rf230_async_state_change(struct at86rf230_local *lp,
			     struct at86rf230_state_change *ctx,
			     const u8 state, void (*complete)(void *context))
{
	/* Initialization for the state change context */
	ctx->to_state = state;
	ctx->complete = complete;
	at86rf230_async_read_reg(lp, RG_TRX_STATUS, ctx,
				 at86rf230_async_state_change_start);
}
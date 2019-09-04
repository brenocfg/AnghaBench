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
struct skl_wrpll_context {int /*<<< orphan*/  min_deviation; } ;

/* Variables and functions */
 int /*<<< orphan*/  U64_MAX ; 
 int /*<<< orphan*/  memset (struct skl_wrpll_context*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void skl_wrpll_context_init(struct skl_wrpll_context *ctx)
{
	memset(ctx, 0, sizeof(*ctx));

	ctx->min_deviation = U64_MAX;
}
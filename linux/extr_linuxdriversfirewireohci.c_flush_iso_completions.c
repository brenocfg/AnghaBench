#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* sc ) (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  callback_data; TYPE_1__ callback; } ;
struct iso_context {scalar_t__ header_length; TYPE_2__ base; int /*<<< orphan*/  header; int /*<<< orphan*/  last_timestamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flush_iso_completions(struct iso_context *ctx)
{
	ctx->base.callback.sc(&ctx->base, ctx->last_timestamp,
			      ctx->header_length, ctx->header,
			      ctx->base.callback_data);
	ctx->header_length = 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uld_ctx {int dummy; } ;
struct chcr_context {TYPE_1__* dev; } ;
struct TYPE_2__ {struct uld_ctx* u_ctx; } ;

/* Variables and functions */

__attribute__((used)) static inline struct uld_ctx *ULD_CTX(struct chcr_context *ctx)
{
	return ctx->dev->u_ctx;
}
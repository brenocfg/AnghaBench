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
struct TYPE_4__ {scalar_t__ d_len; int /*<<< orphan*/ * d_buf; scalar_t__ n_len; int /*<<< orphan*/ * n_buf; scalar_t__ e_len; int /*<<< orphan*/ * e_buf; } ;
struct TYPE_3__ {TYPE_2__ rsa; } ;
struct ccp_ctx {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ccp_rsa_free_key_bufs(struct ccp_ctx *ctx)
{
	/* Clean up old key data */
	kzfree(ctx->u.rsa.e_buf);
	ctx->u.rsa.e_buf = NULL;
	ctx->u.rsa.e_len = 0;
	kzfree(ctx->u.rsa.n_buf);
	ctx->u.rsa.n_buf = NULL;
	ctx->u.rsa.n_len = 0;
	kzfree(ctx->u.rsa.d_buf);
	ctx->u.rsa.d_buf = NULL;
	ctx->u.rsa.d_len = 0;
}
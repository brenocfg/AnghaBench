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
struct chcr_authenc_ctx {int dummy; } ;
struct chcr_aead_ctx {TYPE_1__* ctx; } ;
struct TYPE_2__ {struct chcr_authenc_ctx* authenc; } ;

/* Variables and functions */

__attribute__((used)) static inline struct chcr_authenc_ctx *AUTHENC_CTX(struct chcr_aead_ctx *gctx)
{
	return gctx->ctx->authenc;
}
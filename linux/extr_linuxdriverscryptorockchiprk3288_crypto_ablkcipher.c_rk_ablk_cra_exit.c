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
struct rk_cipher_ctx {TYPE_1__* dev; } ;
struct crypto_tfm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable_clk ) (TYPE_1__*) ;scalar_t__ addr_vir; } ;

/* Variables and functions */
 struct rk_cipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void rk_ablk_cra_exit(struct crypto_tfm *tfm)
{
	struct rk_cipher_ctx *ctx = crypto_tfm_ctx(tfm);

	free_page((unsigned long)ctx->dev->addr_vir);
	ctx->dev->disable_clk(ctx->dev);
}
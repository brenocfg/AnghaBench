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
struct rk_ahash_ctx {TYPE_1__* dev; } ;
struct crypto_tfm {int dummy; } ;
struct TYPE_2__ {void (* disable_clk ) (TYPE_1__*) ;scalar_t__ addr_vir; } ;

/* Variables and functions */
 struct rk_ahash_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 void stub1 (TYPE_1__*) ; 

__attribute__((used)) static void rk_cra_hash_exit(struct crypto_tfm *tfm)
{
	struct rk_ahash_ctx *tctx = crypto_tfm_ctx(tfm);

	free_page((unsigned long)tctx->dev->addr_vir);
	return tctx->dev->disable_clk(tctx->dev);
}
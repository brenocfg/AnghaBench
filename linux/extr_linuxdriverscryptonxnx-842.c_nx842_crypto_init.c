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
struct nx842_driver {int /*<<< orphan*/  workmem_size; } ;
struct nx842_crypto_ctx {int /*<<< orphan*/ * dbounce; int /*<<< orphan*/ * sbounce; int /*<<< orphan*/  wmem; struct nx842_driver* driver; int /*<<< orphan*/  lock; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOUNCE_BUFFER_ORDER ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nx842_crypto_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int nx842_crypto_init(struct crypto_tfm *tfm, struct nx842_driver *driver)
{
	struct nx842_crypto_ctx *ctx = crypto_tfm_ctx(tfm);

	spin_lock_init(&ctx->lock);
	ctx->driver = driver;
	ctx->wmem = kmalloc(driver->workmem_size, GFP_KERNEL);
	ctx->sbounce = (u8 *)__get_free_pages(GFP_KERNEL, BOUNCE_BUFFER_ORDER);
	ctx->dbounce = (u8 *)__get_free_pages(GFP_KERNEL, BOUNCE_BUFFER_ORDER);
	if (!ctx->wmem || !ctx->sbounce || !ctx->dbounce) {
		kfree(ctx->wmem);
		free_page((unsigned long)ctx->sbounce);
		free_page((unsigned long)ctx->dbounce);
		return -ENOMEM;
	}

	return 0;
}
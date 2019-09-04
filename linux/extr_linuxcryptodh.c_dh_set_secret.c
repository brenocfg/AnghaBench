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
struct dh_ctx {int /*<<< orphan*/  xa; } ;
struct dh {int /*<<< orphan*/  key_size; int /*<<< orphan*/  key; } ;
struct crypto_kpp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ crypto_dh_decode_key (void const*,unsigned int,struct dh*) ; 
 int /*<<< orphan*/  dh_clear_ctx (struct dh_ctx*) ; 
 struct dh_ctx* dh_get_ctx (struct crypto_kpp*) ; 
 scalar_t__ dh_set_params (struct dh_ctx*,struct dh*) ; 
 int /*<<< orphan*/  mpi_read_raw_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dh_set_secret(struct crypto_kpp *tfm, const void *buf,
			 unsigned int len)
{
	struct dh_ctx *ctx = dh_get_ctx(tfm);
	struct dh params;

	/* Free the old MPI key if any */
	dh_clear_ctx(ctx);

	if (crypto_dh_decode_key(buf, len, &params) < 0)
		goto err_clear_ctx;

	if (dh_set_params(ctx, &params) < 0)
		goto err_clear_ctx;

	ctx->xa = mpi_read_raw_data(params.key, params.key_size);
	if (!ctx->xa)
		goto err_clear_ctx;

	return 0;

err_clear_ctx:
	dh_clear_ctx(ctx);
	return -EINVAL;
}
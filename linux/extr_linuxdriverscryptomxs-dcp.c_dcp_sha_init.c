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
struct TYPE_2__ {int /*<<< orphan*/  cra_name; } ;
struct hash_alg_common {TYPE_1__ base; } ;
struct dcp_async_ctx {int /*<<< orphan*/  mutex; int /*<<< orphan*/  chan; scalar_t__ hot; scalar_t__ fill; int /*<<< orphan*/  alg; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCP_CHAN_HASH_SHA ; 
 int /*<<< orphan*/  MXS_DCP_CONTROL1_HASH_SELECT_SHA1 ; 
 int /*<<< orphan*/  MXS_DCP_CONTROL1_HASH_SELECT_SHA256 ; 
 struct dcp_async_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 struct hash_alg_common* crypto_hash_alg_common (struct crypto_ahash*) ; 
 int /*<<< orphan*/  memset (struct dcp_async_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int dcp_sha_init(struct ahash_request *req)
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct dcp_async_ctx *actx = crypto_ahash_ctx(tfm);

	struct hash_alg_common *halg = crypto_hash_alg_common(tfm);

	/*
	 * Start hashing session. The code below only inits the
	 * hashing session context, nothing more.
	 */
	memset(actx, 0, sizeof(*actx));

	if (strcmp(halg->base.cra_name, "sha1") == 0)
		actx->alg = MXS_DCP_CONTROL1_HASH_SELECT_SHA1;
	else
		actx->alg = MXS_DCP_CONTROL1_HASH_SELECT_SHA256;

	actx->fill = 0;
	actx->hot = 0;
	actx->chan = DCP_CHAN_HASH_SHA;

	mutex_init(&actx->mutex);

	return 0;
}
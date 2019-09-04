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
struct TYPE_2__ {int /*<<< orphan*/  pub; } ;
struct rsa_edesc {int /*<<< orphan*/  hw_desc; TYPE_1__ pdb; } ;
struct device {int dummy; } ;
struct crypto_akcipher {int dummy; } ;
struct caam_rsa_key {scalar_t__ n_sz; int /*<<< orphan*/  e; int /*<<< orphan*/  n; } ;
struct caam_rsa_ctx {struct device* dev; struct caam_rsa_key key; } ;
struct akcipher_request {scalar_t__ dst_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_RSA_PUB_LEN ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int EOVERFLOW ; 
 scalar_t__ IS_ERR (struct rsa_edesc*) ; 
 int PTR_ERR (struct rsa_edesc*) ; 
 struct caam_rsa_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 int caam_jr_enqueue (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct akcipher_request*) ; 
 struct crypto_akcipher* crypto_akcipher_reqtfm (struct akcipher_request*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  init_rsa_pub_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct rsa_edesc*) ; 
 struct rsa_edesc* rsa_edesc_alloc (struct akcipher_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsa_io_unmap (struct device*,struct rsa_edesc*,struct akcipher_request*) ; 
 int /*<<< orphan*/  rsa_pub_done ; 
 int /*<<< orphan*/  rsa_pub_unmap (struct device*,struct rsa_edesc*,struct akcipher_request*) ; 
 int set_rsa_pub_pdb (struct akcipher_request*,struct rsa_edesc*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int caam_rsa_enc(struct akcipher_request *req)
{
	struct crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	struct caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	struct caam_rsa_key *key = &ctx->key;
	struct device *jrdev = ctx->dev;
	struct rsa_edesc *edesc;
	int ret;

	if (unlikely(!key->n || !key->e))
		return -EINVAL;

	if (req->dst_len < key->n_sz) {
		req->dst_len = key->n_sz;
		dev_err(jrdev, "Output buffer length less than parameter n\n");
		return -EOVERFLOW;
	}

	/* Allocate extended descriptor */
	edesc = rsa_edesc_alloc(req, DESC_RSA_PUB_LEN);
	if (IS_ERR(edesc))
		return PTR_ERR(edesc);

	/* Set RSA Encrypt Protocol Data Block */
	ret = set_rsa_pub_pdb(req, edesc);
	if (ret)
		goto init_fail;

	/* Initialize Job Descriptor */
	init_rsa_pub_desc(edesc->hw_desc, &edesc->pdb.pub);

	ret = caam_jr_enqueue(jrdev, edesc->hw_desc, rsa_pub_done, req);
	if (!ret)
		return -EINPROGRESS;

	rsa_pub_unmap(jrdev, edesc, req);

init_fail:
	rsa_io_unmap(jrdev, edesc, req);
	kfree(edesc);
	return ret;
}
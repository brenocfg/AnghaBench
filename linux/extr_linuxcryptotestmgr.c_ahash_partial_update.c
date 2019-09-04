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
struct scatterlist {int dummy; } ;
struct hash_testvec {int /*<<< orphan*/ * tap; int /*<<< orphan*/  plaintext; } ;
struct crypto_wait {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct ahash_request {int dummy; } ;
typedef  int /*<<< orphan*/  guard ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int ahash_guard_result (char*,int,int) ; 
 struct ahash_request* ahash_request_alloc (struct crypto_ahash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahash_request_free (struct ahash_request*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct crypto_wait*) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,struct scatterlist*,char*,int /*<<< orphan*/ ) ; 
 int crypto_ahash_digestsize (struct crypto_ahash*) ; 
 int crypto_ahash_export (struct ahash_request*,char*) ; 
 int crypto_ahash_import (struct ahash_request*,char*) ; 
 int /*<<< orphan*/  crypto_ahash_reqtfm (struct ahash_request*) ; 
 int crypto_ahash_statesize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_update (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_req_done ; 
 int crypto_wait_req (int /*<<< orphan*/ ,struct crypto_wait*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memcpy (void*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ahash_partial_update(struct ahash_request **preq,
	struct crypto_ahash *tfm, const struct hash_testvec *template,
	void *hash_buff, int k, int temp, struct scatterlist *sg,
	const char *algo, char *result, struct crypto_wait *wait)
{
	char *state;
	struct ahash_request *req;
	int statesize, ret = -EINVAL;
	static const unsigned char guard[] = { 0x00, 0xba, 0xad, 0x00 };
	int digestsize = crypto_ahash_digestsize(tfm);

	req = *preq;
	statesize = crypto_ahash_statesize(
			crypto_ahash_reqtfm(req));
	state = kmalloc(statesize + sizeof(guard), GFP_KERNEL);
	if (!state) {
		pr_err("alg: hash: Failed to alloc state for %s\n", algo);
		goto out_nostate;
	}
	memcpy(state + statesize, guard, sizeof(guard));
	memset(result, 1, digestsize);
	ret = crypto_ahash_export(req, state);
	WARN_ON(memcmp(state + statesize, guard, sizeof(guard)));
	if (ret) {
		pr_err("alg: hash: Failed to export() for %s\n", algo);
		goto out;
	}
	ret = ahash_guard_result(result, 1, digestsize);
	if (ret) {
		pr_err("alg: hash: Failed, export used req->result for %s\n",
		       algo);
		goto out;
	}
	ahash_request_free(req);
	req = ahash_request_alloc(tfm, GFP_KERNEL);
	if (!req) {
		pr_err("alg: hash: Failed to alloc request for %s\n", algo);
		goto out_noreq;
	}
	ahash_request_set_callback(req,
		CRYPTO_TFM_REQ_MAY_BACKLOG,
		crypto_req_done, wait);

	memcpy(hash_buff, template->plaintext + temp,
		template->tap[k]);
	sg_init_one(&sg[0], hash_buff, template->tap[k]);
	ahash_request_set_crypt(req, sg, result, template->tap[k]);
	ret = crypto_ahash_import(req, state);
	if (ret) {
		pr_err("alg: hash: Failed to import() for %s\n", algo);
		goto out;
	}
	ret = ahash_guard_result(result, 1, digestsize);
	if (ret) {
		pr_err("alg: hash: Failed, import used req->result for %s\n",
		       algo);
		goto out;
	}
	ret = crypto_wait_req(crypto_ahash_update(req), wait);
	if (ret)
		goto out;
	*preq = req;
	ret = 0;
	goto out_noreq;
out:
	ahash_request_free(req);
out_noreq:
	kfree(state);
out_nostate:
	return ret;
}
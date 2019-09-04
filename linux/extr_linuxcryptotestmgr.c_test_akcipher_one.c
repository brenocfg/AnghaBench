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
struct crypto_wait {int dummy; } ;
struct crypto_akcipher {int dummy; } ;
struct akcipher_testvec {unsigned int m_size; unsigned int c_size; int /*<<< orphan*/  m; scalar_t__ siggen_sigver_test; int /*<<< orphan*/  c; scalar_t__ public_key_vec; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;
struct akcipher_request {unsigned int dst_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ WARN_ON (int) ; 
 int XBUFSIZE ; 
 struct akcipher_request* akcipher_request_alloc (struct crypto_akcipher*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  akcipher_request_free (struct akcipher_request*) ; 
 int /*<<< orphan*/  akcipher_request_set_callback (struct akcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct crypto_wait*) ; 
 int /*<<< orphan*/  akcipher_request_set_crypt (struct akcipher_request*,struct scatterlist*,struct scatterlist*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  crypto_akcipher_decrypt (struct akcipher_request*) ; 
 int /*<<< orphan*/  crypto_akcipher_encrypt (struct akcipher_request*) ; 
 unsigned int crypto_akcipher_maxsize (struct crypto_akcipher*) ; 
 int crypto_akcipher_set_priv_key (struct crypto_akcipher*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_akcipher_set_pub_key (struct crypto_akcipher*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_akcipher_sign (struct akcipher_request*) ; 
 int /*<<< orphan*/  crypto_akcipher_verify (struct akcipher_request*) ; 
 int /*<<< orphan*/  crypto_init_wait (struct crypto_wait*) ; 
 int /*<<< orphan*/  crypto_req_done ; 
 int crypto_wait_req (int /*<<< orphan*/ ,struct crypto_wait*) ; 
 int /*<<< orphan*/  hexdump (void*,unsigned int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ memchr_inv (void*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,void*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,void*,unsigned int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,char*,int) ; 
 scalar_t__ testmgr_alloc_buf (char**) ; 
 int /*<<< orphan*/  testmgr_free_buf (char**) ; 

__attribute__((used)) static int test_akcipher_one(struct crypto_akcipher *tfm,
			     const struct akcipher_testvec *vecs)
{
	char *xbuf[XBUFSIZE];
	struct akcipher_request *req;
	void *outbuf_enc = NULL;
	void *outbuf_dec = NULL;
	struct crypto_wait wait;
	unsigned int out_len_max, out_len = 0;
	int err = -ENOMEM;
	struct scatterlist src, dst, src_tab[2];

	if (testmgr_alloc_buf(xbuf))
		return err;

	req = akcipher_request_alloc(tfm, GFP_KERNEL);
	if (!req)
		goto free_xbuf;

	crypto_init_wait(&wait);

	if (vecs->public_key_vec)
		err = crypto_akcipher_set_pub_key(tfm, vecs->key,
						  vecs->key_len);
	else
		err = crypto_akcipher_set_priv_key(tfm, vecs->key,
						   vecs->key_len);
	if (err)
		goto free_req;

	err = -ENOMEM;
	out_len_max = crypto_akcipher_maxsize(tfm);
	outbuf_enc = kzalloc(out_len_max, GFP_KERNEL);
	if (!outbuf_enc)
		goto free_req;

	if (WARN_ON(vecs->m_size > PAGE_SIZE))
		goto free_all;

	memcpy(xbuf[0], vecs->m, vecs->m_size);

	sg_init_table(src_tab, 2);
	sg_set_buf(&src_tab[0], xbuf[0], 8);
	sg_set_buf(&src_tab[1], xbuf[0] + 8, vecs->m_size - 8);
	sg_init_one(&dst, outbuf_enc, out_len_max);
	akcipher_request_set_crypt(req, src_tab, &dst, vecs->m_size,
				   out_len_max);
	akcipher_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				      crypto_req_done, &wait);

	err = crypto_wait_req(vecs->siggen_sigver_test ?
			      /* Run asymmetric signature generation */
			      crypto_akcipher_sign(req) :
			      /* Run asymmetric encrypt */
			      crypto_akcipher_encrypt(req), &wait);
	if (err) {
		pr_err("alg: akcipher: encrypt test failed. err %d\n", err);
		goto free_all;
	}
	if (req->dst_len != vecs->c_size) {
		pr_err("alg: akcipher: encrypt test failed. Invalid output len\n");
		err = -EINVAL;
		goto free_all;
	}
	/* verify that encrypted message is equal to expected */
	if (memcmp(vecs->c, outbuf_enc, vecs->c_size)) {
		pr_err("alg: akcipher: encrypt test failed. Invalid output\n");
		hexdump(outbuf_enc, vecs->c_size);
		err = -EINVAL;
		goto free_all;
	}
	/* Don't invoke decrypt for vectors with public key */
	if (vecs->public_key_vec) {
		err = 0;
		goto free_all;
	}
	outbuf_dec = kzalloc(out_len_max, GFP_KERNEL);
	if (!outbuf_dec) {
		err = -ENOMEM;
		goto free_all;
	}

	if (WARN_ON(vecs->c_size > PAGE_SIZE))
		goto free_all;

	memcpy(xbuf[0], vecs->c, vecs->c_size);

	sg_init_one(&src, xbuf[0], vecs->c_size);
	sg_init_one(&dst, outbuf_dec, out_len_max);
	crypto_init_wait(&wait);
	akcipher_request_set_crypt(req, &src, &dst, vecs->c_size, out_len_max);

	err = crypto_wait_req(vecs->siggen_sigver_test ?
			      /* Run asymmetric signature verification */
			      crypto_akcipher_verify(req) :
			      /* Run asymmetric decrypt */
			      crypto_akcipher_decrypt(req), &wait);
	if (err) {
		pr_err("alg: akcipher: decrypt test failed. err %d\n", err);
		goto free_all;
	}
	out_len = req->dst_len;
	if (out_len < vecs->m_size) {
		pr_err("alg: akcipher: decrypt test failed. "
		       "Invalid output len %u\n", out_len);
		err = -EINVAL;
		goto free_all;
	}
	/* verify that decrypted message is equal to the original msg */
	if (memchr_inv(outbuf_dec, 0, out_len - vecs->m_size) ||
	    memcmp(vecs->m, outbuf_dec + out_len - vecs->m_size,
		   vecs->m_size)) {
		pr_err("alg: akcipher: decrypt test failed. Invalid output\n");
		hexdump(outbuf_dec, out_len);
		err = -EINVAL;
	}
free_all:
	kfree(outbuf_dec);
	kfree(outbuf_enc);
free_req:
	akcipher_request_free(req);
free_xbuf:
	testmgr_free_buf(xbuf);
	return err;
}
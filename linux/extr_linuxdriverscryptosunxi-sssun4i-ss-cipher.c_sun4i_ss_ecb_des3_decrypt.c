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
struct sun4i_tfm_ctx {int keymode; } ;
struct sun4i_cipher_req_ctx {int mode; } ;
struct skcipher_request {int dummy; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int SS_DECRYPTION ; 
 int SS_ECB ; 
 int SS_ENABLED ; 
 int SS_OP_3DES ; 
 struct sun4i_tfm_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 struct sun4i_cipher_req_ctx* skcipher_request_ctx (struct skcipher_request*) ; 
 int sun4i_ss_cipher_poll (struct skcipher_request*) ; 

int sun4i_ss_ecb_des3_decrypt(struct skcipher_request *areq)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(areq);
	struct sun4i_tfm_ctx *op = crypto_skcipher_ctx(tfm);
	struct sun4i_cipher_req_ctx *rctx = skcipher_request_ctx(areq);

	rctx->mode = SS_OP_3DES | SS_ECB | SS_ENABLED | SS_DECRYPTION |
		op->keymode;
	return sun4i_ss_cipher_poll(areq);
}
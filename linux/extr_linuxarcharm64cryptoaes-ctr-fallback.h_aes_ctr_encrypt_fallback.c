#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct skcipher_walk {int nbytes; int total; int /*<<< orphan*/  iv; TYPE_4__ src; TYPE_2__ dst; } ;
struct skcipher_request {int dummy; } ;
struct crypto_aes_ctx {int key_length; int /*<<< orphan*/  key_enc; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  __aes_arm64_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  crypto_inc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  crypto_xor_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int min (int,int) ; 
 int round_down (int,int) ; 
 int skcipher_walk_done (struct skcipher_walk*,int) ; 
 int skcipher_walk_virt (struct skcipher_walk*,struct skcipher_request*,int) ; 

__attribute__((used)) static inline int aes_ctr_encrypt_fallback(struct crypto_aes_ctx *ctx,
					   struct skcipher_request *req)
{
	struct skcipher_walk walk;
	u8 buf[AES_BLOCK_SIZE];
	int err;

	err = skcipher_walk_virt(&walk, req, true);

	while (walk.nbytes > 0) {
		u8 *dst = walk.dst.virt.addr;
		u8 *src = walk.src.virt.addr;
		int nbytes = walk.nbytes;
		int tail = 0;

		if (nbytes < walk.total) {
			nbytes = round_down(nbytes, AES_BLOCK_SIZE);
			tail = walk.nbytes % AES_BLOCK_SIZE;
		}

		do {
			int bsize = min(nbytes, AES_BLOCK_SIZE);

			__aes_arm64_encrypt(ctx->key_enc, buf, walk.iv,
					    6 + ctx->key_length / 4);
			crypto_xor_cpy(dst, src, buf, bsize);
			crypto_inc(walk.iv, AES_BLOCK_SIZE);

			dst += AES_BLOCK_SIZE;
			src += AES_BLOCK_SIZE;
			nbytes -= AES_BLOCK_SIZE;
		} while (nbytes > 0);

		err = skcipher_walk_done(&walk, tail);
	}
	return err;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_9__ {int /*<<< orphan*/  addr; } ;
struct TYPE_10__ {TYPE_3__ virt; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_1__ virt; } ;
struct skcipher_walk {unsigned int nbytes; int /*<<< orphan*/  iv; TYPE_4__ src; TYPE_2__ dst; } ;
struct skcipher_request {int dummy; } ;
struct crypto_skcipher {int dummy; } ;
struct TYPE_12__ {scalar_t__ key_enc; } ;
struct TYPE_11__ {int key_length; scalar_t__ key_enc; } ;
struct crypto_aes_xts_ctx {TYPE_6__ key2; TYPE_5__ key1; } ;

/* Variables and functions */
 unsigned int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  aes_xts_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct crypto_aes_xts_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  kernel_neon_begin () ; 
 int /*<<< orphan*/  kernel_neon_end () ; 
 int skcipher_walk_done (struct skcipher_walk*,unsigned int) ; 
 int skcipher_walk_virt (struct skcipher_walk*,struct skcipher_request*,int) ; 

__attribute__((used)) static int xts_encrypt(struct skcipher_request *req)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct crypto_aes_xts_ctx *ctx = crypto_skcipher_ctx(tfm);
	int err, first, rounds = 6 + ctx->key1.key_length / 4;
	struct skcipher_walk walk;
	unsigned int blocks;

	err = skcipher_walk_virt(&walk, req, false);

	for (first = 1; (blocks = (walk.nbytes / AES_BLOCK_SIZE)); first = 0) {
		kernel_neon_begin();
		aes_xts_encrypt(walk.dst.virt.addr, walk.src.virt.addr,
				(u8 *)ctx->key1.key_enc, rounds, blocks,
				(u8 *)ctx->key2.key_enc, walk.iv, first);
		kernel_neon_end();
		err = skcipher_walk_done(&walk, walk.nbytes % AES_BLOCK_SIZE);
	}

	return err;
}
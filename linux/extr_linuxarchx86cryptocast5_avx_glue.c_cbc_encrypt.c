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
typedef  int u64 ;
struct TYPE_7__ {scalar_t__ addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {scalar_t__ addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct skcipher_walk {unsigned int nbytes; scalar_t__ iv; TYPE_4__ dst; TYPE_2__ src; } ;
struct skcipher_request {int dummy; } ;
struct crypto_skcipher {int dummy; } ;
struct cast5_ctx {int dummy; } ;

/* Variables and functions */
 unsigned int CAST5_BLOCK_SIZE ; 
 int /*<<< orphan*/  __cast5_encrypt (struct cast5_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct cast5_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int skcipher_walk_done (struct skcipher_walk*,unsigned int) ; 
 int skcipher_walk_virt (struct skcipher_walk*,struct skcipher_request*,int) ; 

__attribute__((used)) static int cbc_encrypt(struct skcipher_request *req)
{
	const unsigned int bsize = CAST5_BLOCK_SIZE;
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct cast5_ctx *ctx = crypto_skcipher_ctx(tfm);
	struct skcipher_walk walk;
	unsigned int nbytes;
	int err;

	err = skcipher_walk_virt(&walk, req, false);

	while ((nbytes = walk.nbytes)) {
		u64 *src = (u64 *)walk.src.virt.addr;
		u64 *dst = (u64 *)walk.dst.virt.addr;
		u64 *iv = (u64 *)walk.iv;

		do {
			*dst = *src ^ *iv;
			__cast5_encrypt(ctx, (u8 *)dst, (u8 *)dst);
			iv = dst;
			src++;
			dst++;
			nbytes -= bsize;
		} while (nbytes >= bsize);

		*(u64 *)walk.iv = *iv;
		err = skcipher_walk_done(&walk, nbytes);
	}

	return err;
}
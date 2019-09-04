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
struct scatterlist {int dummy; } ;
struct ppc_aes_ctx {int /*<<< orphan*/  rounds; int /*<<< orphan*/  key_enc; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; int /*<<< orphan*/  iv; TYPE_4__ src; TYPE_2__ dst; } ;
struct blkcipher_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_SLEEP ; 
 unsigned int MAX_BYTES ; 
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 int /*<<< orphan*/  blkcipher_walk_init (struct blkcipher_walk*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 int blkcipher_walk_virt_block (struct blkcipher_desc*,struct blkcipher_walk*,int) ; 
 struct ppc_aes_ctx* crypto_blkcipher_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppc_crypt_ctr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spe_begin () ; 
 int /*<<< orphan*/  spe_end () ; 

__attribute__((used)) static int ppc_ctr_crypt(struct blkcipher_desc *desc, struct scatterlist *dst,
			 struct scatterlist *src, unsigned int nbytes)
{
	struct ppc_aes_ctx *ctx = crypto_blkcipher_ctx(desc->tfm);
	struct blkcipher_walk walk;
	unsigned int pbytes, ubytes;
	int err;

	desc->flags &= ~CRYPTO_TFM_REQ_MAY_SLEEP;
	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt_block(desc, &walk, AES_BLOCK_SIZE);

	while ((pbytes = walk.nbytes)) {
		pbytes = pbytes > MAX_BYTES ? MAX_BYTES : pbytes;
		pbytes = pbytes == nbytes ?
			 nbytes : pbytes & ~(AES_BLOCK_SIZE - 1);
		ubytes = walk.nbytes - pbytes;

		spe_begin();
		ppc_crypt_ctr(walk.dst.virt.addr, walk.src.virt.addr,
			      ctx->key_enc, ctx->rounds, pbytes , walk.iv);
		spe_end();

		nbytes -= pbytes;
		err = blkcipher_walk_done(desc, &walk, ubytes);
	}

	return err;
}
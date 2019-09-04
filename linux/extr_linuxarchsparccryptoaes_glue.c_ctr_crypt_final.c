#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct crypto_sparc64_aes_ctx {int /*<<< orphan*/ * key; TYPE_3__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_7__ {TYPE_1__ virt; } ;
struct TYPE_9__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_10__ {TYPE_4__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; TYPE_2__ dst; TYPE_5__ src; int /*<<< orphan*/ * iv; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* ecb_encrypt ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  crypto_inc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  crypto_xor_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ctr_crypt_final(struct crypto_sparc64_aes_ctx *ctx,
			    struct blkcipher_walk *walk)
{
	u8 *ctrblk = walk->iv;
	u64 keystream[AES_BLOCK_SIZE / sizeof(u64)];
	u8 *src = walk->src.virt.addr;
	u8 *dst = walk->dst.virt.addr;
	unsigned int nbytes = walk->nbytes;

	ctx->ops->ecb_encrypt(&ctx->key[0], (const u64 *)ctrblk,
			      keystream, AES_BLOCK_SIZE);
	crypto_xor_cpy(dst, (u8 *) keystream, src, nbytes);
	crypto_inc(ctrblk, AES_BLOCK_SIZE);
}
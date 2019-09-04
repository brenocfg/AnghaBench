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
struct TYPE_8__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_7__ {TYPE_4__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct skcipher_walk {unsigned int nbytes; int /*<<< orphan*/ * iv; TYPE_3__ dst; TYPE_2__ src; } ;
struct skcipher_request {int dummy; } ;
struct crypto_cipher {int dummy; } ;

/* Variables and functions */
 int crypto_cipher_blocksize (struct crypto_cipher*) ; 
 int /*<<< orphan*/  crypto_cipher_encrypt_one (struct crypto_cipher*,int /*<<< orphan*/ *,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  crypto_xor (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  crypto_xor_cpy (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int crypto_pcbc_encrypt_segment(struct skcipher_request *req,
				       struct skcipher_walk *walk,
				       struct crypto_cipher *tfm)
{
	int bsize = crypto_cipher_blocksize(tfm);
	unsigned int nbytes = walk->nbytes;
	u8 *src = walk->src.virt.addr;
	u8 *dst = walk->dst.virt.addr;
	u8 * const iv = walk->iv;

	do {
		crypto_xor(iv, src, bsize);
		crypto_cipher_encrypt_one(tfm, dst, iv);
		crypto_xor_cpy(iv, dst, src, bsize);

		src += bsize;
		dst += bsize;
	} while ((nbytes -= bsize) >= bsize);

	return nbytes;
}
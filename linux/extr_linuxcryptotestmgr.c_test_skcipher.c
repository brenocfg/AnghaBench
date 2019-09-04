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
struct crypto_skcipher {int /*<<< orphan*/  base; } ;
struct cipher_testvec {int dummy; } ;

/* Variables and functions */
 int __test_skcipher (struct crypto_skcipher*,int,struct cipher_testvec const*,unsigned int,int,unsigned int) ; 
 unsigned int crypto_tfm_alg_alignmask (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_skcipher(struct crypto_skcipher *tfm, int enc,
			 const struct cipher_testvec *template,
			 unsigned int tcount)
{
	unsigned int alignmask;
	int ret;

	/* test 'dst == src' case */
	ret = __test_skcipher(tfm, enc, template, tcount, false, 0);
	if (ret)
		return ret;

	/* test 'dst != src' case */
	ret = __test_skcipher(tfm, enc, template, tcount, true, 0);
	if (ret)
		return ret;

	/* test unaligned buffers, check with one byte offset */
	ret = __test_skcipher(tfm, enc, template, tcount, true, 1);
	if (ret)
		return ret;

	alignmask = crypto_tfm_alg_alignmask(&tfm->base);
	if (alignmask) {
		/* Check if alignment mask for tfm is correctly set. */
		ret = __test_skcipher(tfm, enc, template, tcount, true,
				      alignmask + 1);
		if (ret)
			return ret;
	}

	return 0;
}
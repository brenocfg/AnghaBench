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
struct hash_testvec {int dummy; } ;
struct crypto_ahash {int /*<<< orphan*/  base; } ;
typedef  enum hash_test { ____Placeholder_hash_test } hash_test ;

/* Variables and functions */
 int __test_hash (struct crypto_ahash*,struct hash_testvec const*,unsigned int,int,unsigned int) ; 
 unsigned int crypto_tfm_alg_alignmask (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_hash(struct crypto_ahash *tfm,
		     const struct hash_testvec *template,
		     unsigned int tcount, enum hash_test test_type)
{
	unsigned int alignmask;
	int ret;

	ret = __test_hash(tfm, template, tcount, test_type, 0);
	if (ret)
		return ret;

	/* test unaligned buffers, check with one byte offset */
	ret = __test_hash(tfm, template, tcount, test_type, 1);
	if (ret)
		return ret;

	alignmask = crypto_tfm_alg_alignmask(&tfm->base);
	if (alignmask) {
		/* Check if alignment mask for tfm is correctly set. */
		ret = __test_hash(tfm, template, tcount, test_type,
				  alignmask + 1);
		if (ret)
			return ret;
	}

	return 0;
}
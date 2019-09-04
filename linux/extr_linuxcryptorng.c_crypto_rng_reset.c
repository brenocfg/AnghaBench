#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct crypto_rng {int dummy; } ;
struct TYPE_2__ {int (* seed ) (struct crypto_rng*,int /*<<< orphan*/  const*,unsigned int) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* crypto_rng_alg (struct crypto_rng*) ; 
 int get_random_bytes_wait (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 
 int stub1 (struct crypto_rng*,int /*<<< orphan*/  const*,unsigned int) ; 

int crypto_rng_reset(struct crypto_rng *tfm, const u8 *seed, unsigned int slen)
{
	u8 *buf = NULL;
	int err;

	if (!seed && slen) {
		buf = kmalloc(slen, GFP_KERNEL);
		if (!buf)
			return -ENOMEM;

		err = get_random_bytes_wait(buf, slen);
		if (err)
			goto out;
		seed = buf;
	}

	err = crypto_rng_alg(tfm)->seed(tfm, seed, slen);
out:
	kzfree(buf);
	return err;
}
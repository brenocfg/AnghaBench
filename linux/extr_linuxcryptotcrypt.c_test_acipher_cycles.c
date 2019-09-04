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
struct skcipher_request {int dummy; } ;
typedef  scalar_t__ cycles_t ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_skcipher_decrypt (struct skcipher_request*) ; 
 int /*<<< orphan*/  crypto_skcipher_encrypt (struct skcipher_request*) ; 
 int do_one_acipher_op (struct skcipher_request*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_cycles () ; 
 int /*<<< orphan*/  pr_cont (char*,unsigned long,int) ; 

__attribute__((used)) static int test_acipher_cycles(struct skcipher_request *req, int enc,
			       int blen)
{
	unsigned long cycles = 0;
	int ret = 0;
	int i;

	/* Warm-up run. */
	for (i = 0; i < 4; i++) {
		if (enc)
			ret = do_one_acipher_op(req,
						crypto_skcipher_encrypt(req));
		else
			ret = do_one_acipher_op(req,
						crypto_skcipher_decrypt(req));

		if (ret)
			goto out;
	}

	/* The real thing. */
	for (i = 0; i < 8; i++) {
		cycles_t start, end;

		start = get_cycles();
		if (enc)
			ret = do_one_acipher_op(req,
						crypto_skcipher_encrypt(req));
		else
			ret = do_one_acipher_op(req,
						crypto_skcipher_decrypt(req));
		end = get_cycles();

		if (ret)
			goto out;

		cycles += end - start;
	}

out:
	if (ret == 0)
		pr_cont("1 operation in %lu cycles (%d bytes)\n",
			(cycles + 4) / 8, blen);

	return ret;
}
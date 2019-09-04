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
typedef  int u32 ;
struct test_mb_skcipher_data {int dummy; } ;
typedef  scalar_t__ cycles_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int do_mult_acipher_op (struct test_mb_skcipher_data*,int,int,int*) ; 
 scalar_t__ get_cycles () ; 
 int* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int /*<<< orphan*/  pr_cont (char*,unsigned long,int) ; 

__attribute__((used)) static int test_mb_acipher_cycles(struct test_mb_skcipher_data *data, int enc,
			       int blen, u32 num_mb)
{
	unsigned long cycles = 0;
	int ret = 0;
	int i;
	int *rc;

	rc = kcalloc(num_mb, sizeof(*rc), GFP_KERNEL);
	if (!rc)
		return -ENOMEM;

	/* Warm-up run. */
	for (i = 0; i < 4; i++) {
		ret = do_mult_acipher_op(data, enc, num_mb, rc);
		if (ret)
			goto out;
	}

	/* The real thing. */
	for (i = 0; i < 8; i++) {
		cycles_t start, end;

		start = get_cycles();
		ret = do_mult_acipher_op(data, enc, num_mb, rc);
		end = get_cycles();

		if (ret)
			goto out;

		cycles += end - start;
	}

	pr_cont("1 operation in %lu cycles (%d bytes)\n",
		(cycles + 4) / (8 * num_mb), blen);

out:
	kfree(rc);
	return ret;
}
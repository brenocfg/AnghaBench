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
struct test_mb_ahash_data {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int do_mult_ahash_op (struct test_mb_ahash_data*,int,int*) ; 
 unsigned long jiffies ; 
 int* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int /*<<< orphan*/  pr_cont (char*,int,int,long) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int test_mb_ahash_jiffies(struct test_mb_ahash_data *data, int blen,
				 int secs, u32 num_mb)
{
	unsigned long start, end;
	int bcount;
	int ret = 0;
	int *rc;

	rc = kcalloc(num_mb, sizeof(*rc), GFP_KERNEL);
	if (!rc)
		return -ENOMEM;

	for (start = jiffies, end = start + secs * HZ, bcount = 0;
	     time_before(jiffies, end); bcount++) {
		ret = do_mult_ahash_op(data, num_mb, rc);
		if (ret)
			goto out;
	}

	pr_cont("%d operations in %d seconds (%ld bytes)\n",
		bcount * num_mb, secs, (long)bcount * blen * num_mb);

out:
	kfree(rc);
	return ret;
}
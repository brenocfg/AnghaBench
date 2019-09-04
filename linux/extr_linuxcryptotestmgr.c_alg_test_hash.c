#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct hash_testvec {scalar_t__ ksize; } ;
struct TYPE_3__ {unsigned int count; struct hash_testvec* vecs; } ;
struct TYPE_4__ {TYPE_1__ hash; } ;
struct alg_test_desc {int /*<<< orphan*/  alg; TYPE_2__ suite; } ;

/* Variables and functions */
 int EINVAL ; 
 int __alg_test_hash (struct hash_testvec const*,unsigned int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alg_test_hash(const struct alg_test_desc *desc, const char *driver,
			 u32 type, u32 mask)
{
	const struct hash_testvec *template = desc->suite.hash.vecs;
	unsigned int tcount = desc->suite.hash.count;
	unsigned int nr_unkeyed, nr_keyed;
	int err;

	/*
	 * For OPTIONAL_KEY algorithms, we have to do all the unkeyed tests
	 * first, before setting a key on the tfm.  To make this easier, we
	 * require that the unkeyed test vectors (if any) are listed first.
	 */

	for (nr_unkeyed = 0; nr_unkeyed < tcount; nr_unkeyed++) {
		if (template[nr_unkeyed].ksize)
			break;
	}
	for (nr_keyed = 0; nr_unkeyed + nr_keyed < tcount; nr_keyed++) {
		if (!template[nr_unkeyed + nr_keyed].ksize) {
			pr_err("alg: hash: test vectors for %s out of order, "
			       "unkeyed ones must come first\n", desc->alg);
			return -EINVAL;
		}
	}

	err = 0;
	if (nr_unkeyed) {
		err = __alg_test_hash(template, nr_unkeyed, driver, type, mask);
		template += nr_unkeyed;
	}

	if (!err && nr_keyed)
		err = __alg_test_hash(template, nr_keyed, driver, type, mask);

	return err;
}
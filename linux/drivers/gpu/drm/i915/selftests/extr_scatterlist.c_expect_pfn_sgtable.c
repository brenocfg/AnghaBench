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
struct rnd_state {int dummy; } ;
struct pfn_table {int dummy; } ;
typedef  int /*<<< orphan*/  npages_fn_t ;

/* Variables and functions */
 int expect_pfn_sg (struct pfn_table*,int /*<<< orphan*/ ,struct rnd_state*,char const*,unsigned long) ; 
 int expect_pfn_sg_page_iter (struct pfn_table*,char const*,unsigned long) ; 
 int expect_pfn_sgtiter (struct pfn_table*,char const*,unsigned long) ; 

__attribute__((used)) static int expect_pfn_sgtable(struct pfn_table *pt,
			      npages_fn_t npages_fn,
			      struct rnd_state *rnd,
			      const char *who,
			      unsigned long timeout)
{
	int err;

	err = expect_pfn_sg(pt, npages_fn, rnd, who, timeout);
	if (err)
		return err;

	err = expect_pfn_sg_page_iter(pt, who, timeout);
	if (err)
		return err;

	err = expect_pfn_sgtiter(pt, who, timeout);
	if (err)
		return err;

	return 0;
}
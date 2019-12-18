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
struct pagevec {int dummy; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagevec_add (struct pagevec*,struct page*) ; 
 scalar_t__ pagevec_space (struct pagevec*) ; 

__attribute__((used)) static int pool_refill(struct pagevec *pv, gfp_t gfp)
{
	while (pagevec_space(pv)) {
		struct page *p;

		p = alloc_page(gfp);
		if (!p)
			return -ENOMEM;

		pagevec_add(pv, p);
	}

	return 0;
}
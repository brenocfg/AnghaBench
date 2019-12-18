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
struct TYPE_2__ {int /*<<< orphan*/  length; } ;
struct iser_page_vec {int npages; int /*<<< orphan*/ * pages; TYPE_1__ fake_mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  iser_err (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iser_dump_page_vec(struct iser_page_vec *page_vec)
{
	int i;

	iser_err("page vec npages %d data length %lld\n",
		 page_vec->npages, page_vec->fake_mr.length);
	for (i = 0; i < page_vec->npages; i++)
		iser_err("vec[%d]: %llx\n", i, page_vec->pages[i]);
}
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
struct mmc_test_mem {size_t cnt; struct mmc_test_mem* arr; int /*<<< orphan*/  order; int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mmc_test_mem*) ; 

__attribute__((used)) static void mmc_test_free_mem(struct mmc_test_mem *mem)
{
	if (!mem)
		return;
	while (mem->cnt--)
		__free_pages(mem->arr[mem->cnt].page,
			     mem->arr[mem->cnt].order);
	kfree(mem->arr);
	kfree(mem);
}
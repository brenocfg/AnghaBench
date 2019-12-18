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
struct mthca_array {TYPE_1__* page_list; } ;
struct TYPE_2__ {scalar_t__ used; int /*<<< orphan*/ * page; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 TYPE_1__* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 

int mthca_array_init(struct mthca_array *array, int nent)
{
	int npage = (nent * sizeof (void *) + PAGE_SIZE - 1) / PAGE_SIZE;
	int i;

	array->page_list = kmalloc_array(npage, sizeof(*array->page_list),
					 GFP_KERNEL);
	if (!array->page_list)
		return -ENOMEM;

	for (i = 0; i < npage; ++i) {
		array->page_list[i].page = NULL;
		array->page_list[i].used = 0;
	}

	return 0;
}
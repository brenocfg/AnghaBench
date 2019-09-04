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
struct TYPE_2__ {void** page; } ;

/* Variables and functions */
 int MTHCA_ARRAY_MASK ; 
 int PAGE_SHIFT ; 

void *mthca_array_get(struct mthca_array *array, int index)
{
	int p = (index * sizeof (void *)) >> PAGE_SHIFT;

	if (array->page_list[p].page)
		return array->page_list[p].page[index & MTHCA_ARRAY_MASK];
	else
		return NULL;
}
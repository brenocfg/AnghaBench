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
struct page_list {int /*<<< orphan*/  page; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct page_list*) ; 
 struct page_list* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct page_list *alloc_pl(gfp_t gfp)
{
	struct page_list *pl;

	pl = kmalloc(sizeof(*pl), gfp);
	if (!pl)
		return NULL;

	pl->page = alloc_page(gfp);
	if (!pl->page) {
		kfree(pl);
		return NULL;
	}

	return pl;
}
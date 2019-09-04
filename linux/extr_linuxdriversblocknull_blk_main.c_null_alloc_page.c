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
struct nullb_page {int /*<<< orphan*/  bitmap; int /*<<< orphan*/  page; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nullb_page*) ; 
 struct nullb_page* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct nullb_page *null_alloc_page(gfp_t gfp_flags)
{
	struct nullb_page *t_page;

	t_page = kmalloc(sizeof(struct nullb_page), gfp_flags);
	if (!t_page)
		goto out;

	t_page->page = alloc_pages(gfp_flags, 0);
	if (!t_page->page)
		goto out_freepage;

	memset(t_page->bitmap, 0, sizeof(t_page->bitmap));
	return t_page;
out_freepage:
	kfree(t_page);
out:
	return NULL;
}
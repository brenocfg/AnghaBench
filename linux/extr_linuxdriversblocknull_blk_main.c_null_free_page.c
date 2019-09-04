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
struct nullb_page {int /*<<< orphan*/  page; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULLB_PAGE_FREE ; 
 int /*<<< orphan*/  NULLB_PAGE_LOCK ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nullb_page*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void null_free_page(struct nullb_page *t_page)
{
	__set_bit(NULLB_PAGE_FREE, t_page->bitmap);
	if (test_bit(NULLB_PAGE_LOCK, t_page->bitmap))
		return;
	__free_page(t_page->page);
	kfree(t_page);
}
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
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMW_BALLOON_2M_SHIFT ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmballoon_free_page(struct page *page, bool is_2m_page)
{
	if (is_2m_page)
		__free_pages(page, VMW_BALLOON_2M_SHIFT);
	else
		__free_page(page);
}
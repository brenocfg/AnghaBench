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
 int /*<<< orphan*/  SetPageReferenced (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 struct page* compound_head (struct page*) ; 
 scalar_t__ page_count (struct page*) ; 
 int /*<<< orphan*/  page_ref_add (struct page*,int) ; 

__attribute__((used)) static inline void get_head_page_multiple(struct page *page, int nr)
{
	VM_BUG_ON(page != compound_head(page));
	VM_BUG_ON(page_count(page) == 0);
	page_ref_add(page, nr);
	SetPageReferenced(page);
}
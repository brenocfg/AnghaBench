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
struct protection_domain {int /*<<< orphan*/  mode; scalar_t__ pt_root; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PAGE_MODE_6_LEVEL ; 
 int /*<<< orphan*/  PAGE_MODE_NONE ; 
 int /*<<< orphan*/  free_page_list (struct page*) ; 
 struct page* free_sub_pt (unsigned long,int /*<<< orphan*/ ,struct page*) ; 

__attribute__((used)) static void free_pagetable(struct protection_domain *domain)
{
	unsigned long root = (unsigned long)domain->pt_root;
	struct page *freelist = NULL;

	BUG_ON(domain->mode < PAGE_MODE_NONE ||
	       domain->mode > PAGE_MODE_6_LEVEL);

	freelist = free_sub_pt(root, domain->mode, freelist);

	free_page_list(freelist);
}
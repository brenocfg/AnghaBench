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
struct ldt_struct {int slot; unsigned int nr_entries; void* entries; } ;
struct desc_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int LDT_ENTRIES ; 
 int LDT_ENTRY_SIZE ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ldt_struct*) ; 
 struct ldt_struct* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* vzalloc (unsigned int) ; 

__attribute__((used)) static struct ldt_struct *alloc_ldt_struct(unsigned int num_entries)
{
	struct ldt_struct *new_ldt;
	unsigned int alloc_size;

	if (num_entries > LDT_ENTRIES)
		return NULL;

	new_ldt = kmalloc(sizeof(struct ldt_struct), GFP_KERNEL);
	if (!new_ldt)
		return NULL;

	BUILD_BUG_ON(LDT_ENTRY_SIZE != sizeof(struct desc_struct));
	alloc_size = num_entries * LDT_ENTRY_SIZE;

	/*
	 * Xen is very picky: it requires a page-aligned LDT that has no
	 * trailing nonzero bytes in any page that contains LDT descriptors.
	 * Keep it simple: zero the whole allocation and never allocate less
	 * than PAGE_SIZE.
	 */
	if (alloc_size > PAGE_SIZE)
		new_ldt->entries = vzalloc(alloc_size);
	else
		new_ldt->entries = (void *)get_zeroed_page(GFP_KERNEL);

	if (!new_ldt->entries) {
		kfree(new_ldt);
		return NULL;
	}

	/* The new LDT isn't aliased for PTI yet. */
	new_ldt->slot = -1;

	new_ldt->nr_entries = num_entries;
	return new_ldt;
}
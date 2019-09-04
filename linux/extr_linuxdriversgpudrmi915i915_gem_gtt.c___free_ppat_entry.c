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
struct intel_ppat_entry {int /*<<< orphan*/  value; struct intel_ppat* ppat; } ;
struct intel_ppat {unsigned int max_entries; int /*<<< orphan*/  dirty; int /*<<< orphan*/  used; int /*<<< orphan*/  clear_value; struct intel_ppat_entry* entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __free_ppat_entry(struct intel_ppat_entry *entry)
{
	struct intel_ppat *ppat = entry->ppat;
	unsigned int index = entry - ppat->entries;

	GEM_BUG_ON(index >= ppat->max_entries);
	GEM_BUG_ON(!test_bit(index, ppat->used));

	entry->value = ppat->clear_value;
	clear_bit(index, ppat->used);
	set_bit(index, ppat->dirty);
}
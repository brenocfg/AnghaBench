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
typedef  int /*<<< orphan*/  u8 ;
struct intel_ppat_entry {int /*<<< orphan*/  ref; int /*<<< orphan*/  value; struct intel_ppat* ppat; } ;
struct intel_ppat {unsigned int max_entries; int /*<<< orphan*/  dirty; int /*<<< orphan*/  used; struct intel_ppat_entry* entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int test_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct intel_ppat_entry *
__alloc_ppat_entry(struct intel_ppat *ppat, unsigned int index, u8 value)
{
	struct intel_ppat_entry *entry = &ppat->entries[index];

	GEM_BUG_ON(index >= ppat->max_entries);
	GEM_BUG_ON(test_bit(index, ppat->used));

	entry->ppat = ppat;
	entry->value = value;
	kref_init(&entry->ref);
	set_bit(index, ppat->used);
	set_bit(index, ppat->dirty);

	return entry;
}
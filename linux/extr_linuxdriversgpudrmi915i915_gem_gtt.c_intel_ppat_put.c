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
struct intel_ppat_entry {int /*<<< orphan*/  ref; struct intel_ppat* ppat; } ;
struct intel_ppat {struct intel_ppat_entry const* entries; int /*<<< orphan*/  max_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_ppat ; 

void intel_ppat_put(const struct intel_ppat_entry *entry)
{
	struct intel_ppat *ppat = entry->ppat;
	unsigned int index = entry - ppat->entries;

	GEM_BUG_ON(!ppat->max_entries);

	kref_put(&ppat->entries[index].ref, release_ppat);
}
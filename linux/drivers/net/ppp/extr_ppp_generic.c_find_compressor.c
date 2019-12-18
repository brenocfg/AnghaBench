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
struct compressor_entry {struct compressor* comp; } ;
struct compressor {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  compressor_list_lock ; 
 struct compressor_entry* find_comp_entry (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct compressor *
find_compressor(int type)
{
	struct compressor_entry *ce;
	struct compressor *cp = NULL;

	spin_lock(&compressor_list_lock);
	ce = find_comp_entry(type);
	if (ce) {
		cp = ce->comp;
		if (!try_module_get(cp->owner))
			cp = NULL;
	}
	spin_unlock(&compressor_list_lock);
	return cp;
}
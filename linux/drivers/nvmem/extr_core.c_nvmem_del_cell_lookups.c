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
struct nvmem_cell_lookup {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmem_lookup_mutex ; 

void nvmem_del_cell_lookups(struct nvmem_cell_lookup *entries, size_t nentries)
{
	int i;

	mutex_lock(&nvmem_lookup_mutex);
	for (i = 0; i < nentries; i++)
		list_del(&entries[i].node);
	mutex_unlock(&nvmem_lookup_mutex);
}
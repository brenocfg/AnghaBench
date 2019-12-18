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
struct hash_cell {char* name; int /*<<< orphan*/  name_list; } ;

/* Variables and functions */
 scalar_t__ _name_buckets ; 
 int /*<<< orphan*/  dm_hash_cells_mutex ; 
 scalar_t__ hash_str (char*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *__change_cell_name(struct hash_cell *hc, char *new_name)
{
	char *old_name;

	/*
	 * Rename and move the name cell.
	 */
	list_del(&hc->name_list);
	old_name = hc->name;

	mutex_lock(&dm_hash_cells_mutex);
	hc->name = new_name;
	mutex_unlock(&dm_hash_cells_mutex);

	list_add(&hc->name_list, _name_buckets + hash_str(new_name));

	return old_name;
}
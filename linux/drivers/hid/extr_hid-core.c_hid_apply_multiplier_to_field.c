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
struct hid_usage {size_t collection_index; int resolution_multiplier; } ;
struct hid_field {int maxusage; struct hid_usage* usage; } ;
struct hid_device {struct hid_collection* collection; } ;
struct hid_collection {int parent_idx; } ;

/* Variables and functions */

__attribute__((used)) static void hid_apply_multiplier_to_field(struct hid_device *hid,
					  struct hid_field *field,
					  struct hid_collection *multiplier_collection,
					  int effective_multiplier)
{
	struct hid_collection *collection;
	struct hid_usage *usage;
	int i;

	/*
	 * If multiplier_collection is NULL, the multiplier applies
	 * to all fields in the report.
	 * Otherwise, it is the Logical Collection the multiplier applies to
	 * but our field may be in a subcollection of that collection.
	 */
	for (i = 0; i < field->maxusage; i++) {
		usage = &field->usage[i];

		collection = &hid->collection[usage->collection_index];
		while (collection->parent_idx != -1 &&
		       collection != multiplier_collection)
			collection = &hid->collection[collection->parent_idx];

		if (collection->parent_idx != -1 ||
		    multiplier_collection == NULL)
			usage->resolution_multiplier = effective_multiplier;

	}
}
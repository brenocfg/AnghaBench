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
struct ubi_device {int vtbl_slots; int /*<<< orphan*/ * volumes; } ;

/* Variables and functions */
 int UBI_INT_VOL_COUNT ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_eba_replace_table (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_fastmap_destroy_checkmap (int /*<<< orphan*/ ) ; 

void ubi_free_internal_volumes(struct ubi_device *ubi)
{
	int i;

	for (i = ubi->vtbl_slots;
	     i < ubi->vtbl_slots + UBI_INT_VOL_COUNT; i++) {
		ubi_eba_replace_table(ubi->volumes[i], NULL);
		ubi_fastmap_destroy_checkmap(ubi->volumes[i]);
		kfree(ubi->volumes[i]);
	}
}
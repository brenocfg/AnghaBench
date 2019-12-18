#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ubi_wl_entry {int pnum; } ;
struct ubi_device {TYPE_1__* fm; } ;
struct TYPE_2__ {int used_blocks; struct ubi_wl_entry** e; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ubi_wl_entry *ubi_find_fm_block(const struct ubi_device *ubi,
						     int pnum)
{
	int i;

	if (ubi->fm) {
		for (i = 0; i < ubi->fm->used_blocks; i++) {
			if (ubi->fm->e[i]->pnum == pnum)
				return ubi->fm->e[i];
		}
	}

	return NULL;
}
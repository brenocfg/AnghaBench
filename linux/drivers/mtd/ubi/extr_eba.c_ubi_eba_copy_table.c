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
struct ubi_volume {struct ubi_eba_table* eba_tbl; } ;
struct ubi_eba_table {TYPE_1__* entries; } ;
struct TYPE_2__ {int /*<<< orphan*/  pnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  ubi_assert (int /*<<< orphan*/ ) ; 

void ubi_eba_copy_table(struct ubi_volume *vol, struct ubi_eba_table *dst,
			int nentries)
{
	struct ubi_eba_table *src;
	int i;

	ubi_assert(dst && vol && vol->eba_tbl);

	src = vol->eba_tbl;

	for (i = 0; i < nentries; i++)
		dst->entries[i].pnum = src->entries[i].pnum;
}
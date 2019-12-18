#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ubi_volume {TYPE_2__* eba_tbl; } ;
struct ubi_eba_leb_desc {int lnum; int /*<<< orphan*/  pnum; } ;
struct TYPE_4__ {TYPE_1__* entries; } ;
struct TYPE_3__ {int /*<<< orphan*/  pnum; } ;

/* Variables and functions */

void ubi_eba_get_ldesc(struct ubi_volume *vol, int lnum,
		       struct ubi_eba_leb_desc *ldesc)
{
	ldesc->lnum = lnum;
	ldesc->pnum = vol->eba_tbl->entries[lnum].pnum;
}
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
struct TYPE_4__ {TYPE_1__* entries; } ;
struct TYPE_3__ {scalar_t__ pnum; } ;

/* Variables and functions */

bool ubi_eba_is_mapped(struct ubi_volume *vol, int lnum)
{
	return vol->eba_tbl->entries[lnum].pnum >= 0;
}
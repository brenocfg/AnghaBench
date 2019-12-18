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
struct TYPE_2__ {scalar_t__ index; } ;
struct ll_disk {TYPE_1__ mi_le; } ;
struct disk_index_entry {int dummy; } ;
typedef  scalar_t__ dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct disk_index_entry*,scalar_t__,int) ; 

__attribute__((used)) static int metadata_ll_load_ie(struct ll_disk *ll, dm_block_t index,
			       struct disk_index_entry *ie)
{
	memcpy(ie, ll->mi_le.index + index, sizeof(*ie));
	return 0;
}
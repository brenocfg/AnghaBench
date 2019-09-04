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
struct agp_bridge_data {int dummy; } ;
struct _parisc_agp_info {int gatt_entries; unsigned long* gatt; } ;
struct TYPE_2__ {scalar_t__ scratch_page; } ;

/* Variables and functions */
 TYPE_1__* agp_bridge ; 
 struct _parisc_agp_info parisc_agp_info ; 

__attribute__((used)) static int
parisc_agp_create_gatt_table(struct agp_bridge_data *bridge)
{
	struct _parisc_agp_info *info = &parisc_agp_info;
	int i;

	for (i = 0; i < info->gatt_entries; i++) {
		info->gatt[i] = (unsigned long)agp_bridge->scratch_page;
	}

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct nsim_trap_item {int dummy; } ;
struct nsim_trap_data {struct nsim_trap_item* trap_items_arr; } ;
struct nsim_dev {struct nsim_trap_data* trap_data; } ;
struct TYPE_3__ {scalar_t__ id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* nsim_traps_arr ; 

__attribute__((used)) static struct nsim_trap_item *
nsim_dev_trap_item_lookup(struct nsim_dev *nsim_dev, u16 trap_id)
{
	struct nsim_trap_data *nsim_trap_data = nsim_dev->trap_data;
	int i;

	for (i = 0; i < ARRAY_SIZE(nsim_traps_arr); i++) {
		if (nsim_traps_arr[i].id == trap_id)
			return &nsim_trap_data->trap_items_arr[i];
	}

	return NULL;
}
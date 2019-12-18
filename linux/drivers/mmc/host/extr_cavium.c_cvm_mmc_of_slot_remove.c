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
struct cvm_mmc_slot {size_t bus_id; int /*<<< orphan*/  mmc; TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_free_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_remove_host (int /*<<< orphan*/ ) ; 

int cvm_mmc_of_slot_remove(struct cvm_mmc_slot *slot)
{
	mmc_remove_host(slot->mmc);
	slot->host->slot[slot->bus_id] = NULL;
	mmc_free_host(slot->mmc);
	return 0;
}
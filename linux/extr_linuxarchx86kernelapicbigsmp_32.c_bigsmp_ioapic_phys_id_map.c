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
typedef  int /*<<< orphan*/  physid_mask_t ;

/* Variables and functions */
 int /*<<< orphan*/  physids_promote (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bigsmp_ioapic_phys_id_map(physid_mask_t *phys_map, physid_mask_t *retmap)
{
	/* For clustered we don't have a good way to do this yet - hack */
	physids_promote(0xFFL, retmap);
}
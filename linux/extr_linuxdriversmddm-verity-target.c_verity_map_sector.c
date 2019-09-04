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
struct dm_verity {int /*<<< orphan*/  ti; scalar_t__ data_start; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 scalar_t__ dm_target_offset (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static sector_t verity_map_sector(struct dm_verity *v, sector_t bi_sector)
{
	return v->data_start + dm_target_offset(v->ti, bi_sector);
}
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
struct dm_clone_metadata {int /*<<< orphan*/  region_map; } ;

/* Variables and functions */
 scalar_t__ dm_clone_is_hydration_done (struct dm_clone_metadata*) ; 
 scalar_t__ test_bit (unsigned long,int /*<<< orphan*/ ) ; 

bool dm_clone_is_region_hydrated(struct dm_clone_metadata *cmd, unsigned long region_nr)
{
	return dm_clone_is_hydration_done(cmd) || test_bit(region_nr, cmd->region_map);
}
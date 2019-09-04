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
struct dm_target {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int DM_MAPIO_REMAPPED ; 
 int /*<<< orphan*/  linear_map_bio (struct dm_target*,struct bio*) ; 

__attribute__((used)) static int linear_map(struct dm_target *ti, struct bio *bio)
{
	linear_map_bio(ti, bio);

	return DM_MAPIO_REMAPPED;
}
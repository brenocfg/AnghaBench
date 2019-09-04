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
 int DM_MAPIO_KILL ; 

__attribute__((used)) static int io_err_map(struct dm_target *tt, struct bio *bio)
{
	return DM_MAPIO_KILL;
}
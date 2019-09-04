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
struct stripe_head {int generation; } ;
struct r5conf {scalar_t__ reshape_progress; int generation; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 scalar_t__ MaxSector ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static int use_new_offset(struct r5conf *conf, struct stripe_head *sh)
{
	sector_t progress = conf->reshape_progress;
	/* Need a memory barrier to make sure we see the value
	 * of conf->generation, or ->data_offset that was set before
	 * reshape_progress was updated.
	 */
	smp_rmb();
	if (progress == MaxSector)
		return 0;
	if (sh->generation == conf->generation - 1)
		return 0;
	/* We are in a reshape, and this is a new-generation stripe,
	 * so use new_data_offset.
	 */
	return 1;
}
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
struct era {int /*<<< orphan*/  sectors_per_block; TYPE_1__* ti; } ;
typedef  int /*<<< orphan*/  dm_block_t ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_sector_div_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dm_block_t calc_nr_blocks(struct era *era)
{
	return dm_sector_div_up(era->ti->len, era->sectors_per_block);
}
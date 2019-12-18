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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct pmc_reg_map {int /*<<< orphan*/  slp_s0_offset; } ;
struct pmc_dev {struct pmc_reg_map* map; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmc_core_adjust_slp_s0_step (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmc_core_reg_read (struct pmc_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pmc_core_dev_state_get(void *data, u64 *val)
{
	struct pmc_dev *pmcdev = data;
	const struct pmc_reg_map *map = pmcdev->map;
	u32 value;

	value = pmc_core_reg_read(pmcdev, map->slp_s0_offset);
	*val = pmc_core_adjust_slp_s0_step(value);

	return 0;
}
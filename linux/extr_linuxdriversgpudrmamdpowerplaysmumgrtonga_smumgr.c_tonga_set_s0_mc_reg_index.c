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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct tonga_mc_reg_table {size_t last; TYPE_1__* mc_reg_address; } ;
struct TYPE_2__ {int /*<<< orphan*/  s1; int /*<<< orphan*/  s0; } ;

/* Variables and functions */
 scalar_t__ tonga_check_s0_mc_reg_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tonga_set_s0_mc_reg_index(struct tonga_mc_reg_table *table)
{
	uint32_t i;
	uint16_t address;

	for (i = 0; i < table->last; i++) {
		table->mc_reg_address[i].s0 =
			tonga_check_s0_mc_reg_index(table->mc_reg_address[i].s1,
							&address) ?
							address :
						 table->mc_reg_address[i].s1;
	}
	return 0;
}
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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ci_mc_reg_table {size_t last; TYPE_1__* mc_reg_address; } ;
struct TYPE_2__ {int /*<<< orphan*/  s1; int /*<<< orphan*/  s0; } ;

/* Variables and functions */
 scalar_t__ ci_check_s0_mc_reg_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ci_set_s0_mc_reg_index(struct ci_mc_reg_table *table)
{
	u32 i;
	u16 address;

	for (i = 0; i < table->last; i++) {
		table->mc_reg_address[i].s0 =
			ci_check_s0_mc_reg_index(table->mc_reg_address[i].s1, &address) ?
			address : table->mc_reg_address[i].s1;
	}
}
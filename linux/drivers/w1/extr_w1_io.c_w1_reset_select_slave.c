#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct w1_slave {TYPE_1__* master; int /*<<< orphan*/  reg_num; } ;
struct TYPE_4__ {int slave_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  W1_MATCH_ROM ; 
 int /*<<< orphan*/  W1_SKIP_ROM ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ w1_reset_bus (TYPE_1__*) ; 
 int /*<<< orphan*/  w1_write_8 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w1_write_block (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

int w1_reset_select_slave(struct w1_slave *sl)
{
	if (w1_reset_bus(sl->master))
		return -1;

	if (sl->master->slave_count == 1)
		w1_write_8(sl->master, W1_SKIP_ROM);
	else {
		u8 match[9] = {W1_MATCH_ROM, };
		u64 rn = le64_to_cpu(*((u64*)&sl->reg_num));

		memcpy(&match[1], &rn, 8);
		w1_write_block(sl->master, match, 9);
	}
	return 0;
}
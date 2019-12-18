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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ HP_COUNT_G (scalar_t__) ; 
 scalar_t__ HP_COUNT_T5_G (scalar_t__) ; 
 scalar_t__ LP_COUNT_G (scalar_t__) ; 
 scalar_t__ LP_COUNT_T5_G (scalar_t__) ; 
 int /*<<< orphan*/  SGE_DBFIFO_STATUS2_A ; 
 int /*<<< orphan*/  SGE_DBFIFO_STATUS_A ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 scalar_t__ is_t4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int) ; 

__attribute__((used)) static void drain_db_fifo(struct adapter *adap, int usecs)
{
	u32 v1, v2, lp_count, hp_count;

	do {
		v1 = t4_read_reg(adap, SGE_DBFIFO_STATUS_A);
		v2 = t4_read_reg(adap, SGE_DBFIFO_STATUS2_A);
		if (is_t4(adap->params.chip)) {
			lp_count = LP_COUNT_G(v1);
			hp_count = HP_COUNT_G(v1);
		} else {
			lp_count = LP_COUNT_T5_G(v1);
			hp_count = HP_COUNT_T5_G(v2);
		}

		if (lp_count == 0 && hp_count == 0)
			break;
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_timeout(usecs_to_jiffies(usecs));
	} while (1);
}
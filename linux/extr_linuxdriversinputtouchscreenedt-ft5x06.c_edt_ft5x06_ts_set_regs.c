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
struct edt_reg_addr {void* reg_offset; void* reg_gain; void* reg_threshold; int /*<<< orphan*/  reg_num_y; int /*<<< orphan*/  reg_num_x; int /*<<< orphan*/  reg_report_rate; } ;
struct edt_ft5x06_ts_data {int version; struct edt_reg_addr reg_addr; } ;

/* Variables and functions */
#define  EDT_M06 131 
#define  EDT_M09 130 
#define  EDT_M12 129 
#define  GENERIC_FT 128 
 void* M09_REGISTER_GAIN ; 
 int /*<<< orphan*/  M09_REGISTER_NUM_X ; 
 int /*<<< orphan*/  M09_REGISTER_NUM_Y ; 
 void* M09_REGISTER_OFFSET ; 
 void* M09_REGISTER_THRESHOLD ; 
 int /*<<< orphan*/  NO_REGISTER ; 
 void* WORK_REGISTER_GAIN ; 
 int /*<<< orphan*/  WORK_REGISTER_NUM_X ; 
 int /*<<< orphan*/  WORK_REGISTER_NUM_Y ; 
 void* WORK_REGISTER_OFFSET ; 
 int /*<<< orphan*/  WORK_REGISTER_REPORT_RATE ; 
 void* WORK_REGISTER_THRESHOLD ; 

__attribute__((used)) static void
edt_ft5x06_ts_set_regs(struct edt_ft5x06_ts_data *tsdata)
{
	struct edt_reg_addr *reg_addr = &tsdata->reg_addr;

	switch (tsdata->version) {
	case EDT_M06:
		reg_addr->reg_threshold = WORK_REGISTER_THRESHOLD;
		reg_addr->reg_report_rate = WORK_REGISTER_REPORT_RATE;
		reg_addr->reg_gain = WORK_REGISTER_GAIN;
		reg_addr->reg_offset = WORK_REGISTER_OFFSET;
		reg_addr->reg_num_x = WORK_REGISTER_NUM_X;
		reg_addr->reg_num_y = WORK_REGISTER_NUM_Y;
		break;

	case EDT_M09:
	case EDT_M12:
		reg_addr->reg_threshold = M09_REGISTER_THRESHOLD;
		reg_addr->reg_report_rate = NO_REGISTER;
		reg_addr->reg_gain = M09_REGISTER_GAIN;
		reg_addr->reg_offset = M09_REGISTER_OFFSET;
		reg_addr->reg_num_x = M09_REGISTER_NUM_X;
		reg_addr->reg_num_y = M09_REGISTER_NUM_Y;
		break;

	case GENERIC_FT:
		/* this is a guesswork */
		reg_addr->reg_threshold = M09_REGISTER_THRESHOLD;
		reg_addr->reg_gain = M09_REGISTER_GAIN;
		reg_addr->reg_offset = M09_REGISTER_OFFSET;
		break;
	}
}
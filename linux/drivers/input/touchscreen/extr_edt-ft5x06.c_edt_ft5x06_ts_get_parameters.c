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
struct edt_reg_addr {scalar_t__ reg_threshold; scalar_t__ reg_gain; scalar_t__ reg_offset; scalar_t__ reg_offset_x; scalar_t__ reg_offset_y; scalar_t__ reg_report_rate; scalar_t__ reg_num_x; scalar_t__ reg_num_y; } ;
struct edt_ft5x06_ts_data {scalar_t__ version; int num_x; int num_y; void* report_rate; void* offset_y; void* offset_x; void* offset; void* gain; void* threshold; struct edt_reg_addr reg_addr; } ;

/* Variables and functions */
 scalar_t__ EDT_M06 ; 
 scalar_t__ EDT_M09 ; 
 scalar_t__ EDT_M12 ; 
 scalar_t__ NO_REGISTER ; 
 void* edt_ft5x06_register_read (struct edt_ft5x06_ts_data*,scalar_t__) ; 

__attribute__((used)) static void
edt_ft5x06_ts_get_parameters(struct edt_ft5x06_ts_data *tsdata)
{
	struct edt_reg_addr *reg_addr = &tsdata->reg_addr;

	tsdata->threshold = edt_ft5x06_register_read(tsdata,
						     reg_addr->reg_threshold);
	tsdata->gain = edt_ft5x06_register_read(tsdata, reg_addr->reg_gain);
	if (reg_addr->reg_offset != NO_REGISTER)
		tsdata->offset =
			edt_ft5x06_register_read(tsdata, reg_addr->reg_offset);
	if (reg_addr->reg_offset_x != NO_REGISTER)
		tsdata->offset_x = edt_ft5x06_register_read(tsdata,
						reg_addr->reg_offset_x);
	if (reg_addr->reg_offset_y != NO_REGISTER)
		tsdata->offset_y = edt_ft5x06_register_read(tsdata,
						reg_addr->reg_offset_y);
	if (reg_addr->reg_report_rate != NO_REGISTER)
		tsdata->report_rate = edt_ft5x06_register_read(tsdata,
						reg_addr->reg_report_rate);
	if (tsdata->version == EDT_M06 ||
	    tsdata->version == EDT_M09 ||
	    tsdata->version == EDT_M12) {
		tsdata->num_x = edt_ft5x06_register_read(tsdata,
							 reg_addr->reg_num_x);
		tsdata->num_y = edt_ft5x06_register_read(tsdata,
							 reg_addr->reg_num_y);
	} else {
		tsdata->num_x = -1;
		tsdata->num_y = -1;
	}
}
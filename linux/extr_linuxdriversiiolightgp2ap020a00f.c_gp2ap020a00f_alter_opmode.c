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
struct gp2ap020a00f_data {scalar_t__ cur_opmode; } ;
typedef  enum gp2ap020a00f_opmode { ____Placeholder_gp2ap020a00f_opmode } gp2ap020a00f_opmode ;

/* Variables and functions */
 int EINVAL ; 
 int GP2AP020A00F_ADD_MODE ; 
 int GP2AP020A00F_OPMODE_ALS ; 
 scalar_t__ GP2AP020A00F_OPMODE_ALS_AND_PS ; 
 int GP2AP020A00F_OPMODE_PS ; 
 scalar_t__ GP2AP020A00F_OPMODE_SHUTDOWN ; 
 int gp2ap020a00f_set_operation_mode (struct gp2ap020a00f_data*,int) ; 

__attribute__((used)) static int gp2ap020a00f_alter_opmode(struct gp2ap020a00f_data *data,
			enum gp2ap020a00f_opmode diff_mode, int add_sub)
{
	enum gp2ap020a00f_opmode new_mode;

	if (diff_mode != GP2AP020A00F_OPMODE_ALS &&
	    diff_mode != GP2AP020A00F_OPMODE_PS)
		return -EINVAL;

	if (add_sub == GP2AP020A00F_ADD_MODE) {
		if (data->cur_opmode == GP2AP020A00F_OPMODE_SHUTDOWN)
			new_mode =  diff_mode;
		else
			new_mode = GP2AP020A00F_OPMODE_ALS_AND_PS;
	} else {
		if (data->cur_opmode == GP2AP020A00F_OPMODE_ALS_AND_PS)
			new_mode = (diff_mode == GP2AP020A00F_OPMODE_ALS) ?
					GP2AP020A00F_OPMODE_PS :
					GP2AP020A00F_OPMODE_ALS;
		else
			new_mode = GP2AP020A00F_OPMODE_SHUTDOWN;
	}

	return gp2ap020a00f_set_operation_mode(data, new_mode);
}
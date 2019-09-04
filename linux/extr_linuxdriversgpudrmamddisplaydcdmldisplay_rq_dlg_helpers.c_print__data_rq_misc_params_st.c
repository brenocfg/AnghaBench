#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct display_mode_lib {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  req_height; int /*<<< orphan*/  req_width; int /*<<< orphan*/  blk256_height; int /*<<< orphan*/  blk256_width; int /*<<< orphan*/  stored_swath_bytes; int /*<<< orphan*/  full_swath_bytes; } ;
typedef  TYPE_1__ display_data_rq_misc_params_st ;

/* Variables and functions */
 int /*<<< orphan*/  dml_print (char*,...) ; 

void print__data_rq_misc_params_st(struct display_mode_lib *mode_lib, display_data_rq_misc_params_st rq_misc_param)
{
	dml_print("DML_RQ_DLG_CALC: =====================================\n");
	dml_print("DML_RQ_DLG_CALC: DISPLAY_DATA_RQ_MISC_PARAM_ST\n");
	dml_print(
			"DML_RQ_DLG_CALC:     full_swath_bytes   = %0d\n",
			rq_misc_param.full_swath_bytes);
	dml_print(
			"DML_RQ_DLG_CALC:     stored_swath_bytes = %0d\n",
			rq_misc_param.stored_swath_bytes);
	dml_print("DML_RQ_DLG_CALC:     blk256_width       = %0d\n", rq_misc_param.blk256_width);
	dml_print("DML_RQ_DLG_CALC:     blk256_height      = %0d\n", rq_misc_param.blk256_height);
	dml_print("DML_RQ_DLG_CALC:     req_width          = %0d\n", rq_misc_param.req_width);
	dml_print("DML_RQ_DLG_CALC:     req_height         = %0d\n", rq_misc_param.req_height);
	dml_print("DML_RQ_DLG_CALC: =====================================\n");
}
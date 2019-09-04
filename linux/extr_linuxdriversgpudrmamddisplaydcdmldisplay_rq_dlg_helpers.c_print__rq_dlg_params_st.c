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
struct TYPE_3__ {int /*<<< orphan*/  rq_c; int /*<<< orphan*/  rq_l; } ;
typedef  TYPE_1__ display_rq_dlg_params_st ;

/* Variables and functions */
 int /*<<< orphan*/  dml_print (char*) ; 
 int /*<<< orphan*/  print__data_rq_dlg_params_st (struct display_mode_lib*,int /*<<< orphan*/ ) ; 

void print__rq_dlg_params_st(struct display_mode_lib *mode_lib, display_rq_dlg_params_st rq_dlg_param)
{
	dml_print("DML_RQ_DLG_CALC: =====================================\n");
	dml_print("DML_RQ_DLG_CALC: DISPLAY_RQ_DLG_PARAM_ST\n");
	dml_print("DML_RQ_DLG_CALC:  <LUMA>\n");
	print__data_rq_dlg_params_st(mode_lib, rq_dlg_param.rq_l);
	dml_print("DML_RQ_DLG_CALC:  <CHROMA>\n");
	print__data_rq_dlg_params_st(mode_lib, rq_dlg_param.rq_c);
	dml_print("DML_RQ_DLG_CALC: =====================================\n");
}
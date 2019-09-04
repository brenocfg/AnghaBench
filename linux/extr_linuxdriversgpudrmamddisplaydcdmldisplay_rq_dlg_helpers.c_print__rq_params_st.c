#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct display_mode_lib {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  rq_c; int /*<<< orphan*/  rq_l; } ;
struct TYPE_8__ {int /*<<< orphan*/  rq_c; int /*<<< orphan*/  rq_l; } ;
struct TYPE_7__ {int /*<<< orphan*/  rq_c; int /*<<< orphan*/  rq_l; } ;
struct TYPE_9__ {TYPE_1__ misc; TYPE_3__ dlg; TYPE_2__ sizing; } ;
typedef  TYPE_4__ display_rq_params_st ;

/* Variables and functions */
 int /*<<< orphan*/  dml_print (char*) ; 
 int /*<<< orphan*/  print__data_rq_dlg_params_st (struct display_mode_lib*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print__data_rq_misc_params_st (struct display_mode_lib*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print__data_rq_sizing_params_st (struct display_mode_lib*,int /*<<< orphan*/ ) ; 

void print__rq_params_st(struct display_mode_lib *mode_lib, display_rq_params_st rq_param)
{
	dml_print("DML_RQ_DLG_CALC: ***************************\n");
	dml_print("DML_RQ_DLG_CALC: DISPLAY_RQ_PARAM_ST\n");
	dml_print("DML_RQ_DLG_CALC:  <LUMA>\n");
	print__data_rq_sizing_params_st(mode_lib, rq_param.sizing.rq_l);
	dml_print("DML_RQ_DLG_CALC:  <CHROMA> ===\n");
	print__data_rq_sizing_params_st(mode_lib, rq_param.sizing.rq_c);

	dml_print("DML_RQ_DLG_CALC: <LUMA>\n");
	print__data_rq_dlg_params_st(mode_lib, rq_param.dlg.rq_l);
	dml_print("DML_RQ_DLG_CALC: <CHROMA>\n");
	print__data_rq_dlg_params_st(mode_lib, rq_param.dlg.rq_c);

	dml_print("DML_RQ_DLG_CALC: <LUMA>\n");
	print__data_rq_misc_params_st(mode_lib, rq_param.misc.rq_l);
	dml_print("DML_RQ_DLG_CALC: <CHROMA>\n");
	print__data_rq_misc_params_st(mode_lib, rq_param.misc.rq_c);
	dml_print("DML_RQ_DLG_CALC: ***************************\n");
}
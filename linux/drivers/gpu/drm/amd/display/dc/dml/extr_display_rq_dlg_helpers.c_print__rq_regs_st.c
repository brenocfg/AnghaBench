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
struct TYPE_3__ {int /*<<< orphan*/  plane1_base_address; int /*<<< orphan*/  crq_expansion_mode; int /*<<< orphan*/  mrq_expansion_mode; int /*<<< orphan*/  prq_expansion_mode; int /*<<< orphan*/  drq_expansion_mode; int /*<<< orphan*/  rq_regs_c; int /*<<< orphan*/  rq_regs_l; } ;
typedef  TYPE_1__ display_rq_regs_st ;

/* Variables and functions */
 int /*<<< orphan*/  dml_print (char*,...) ; 
 int /*<<< orphan*/  print__data_rq_regs_st (struct display_mode_lib*,int /*<<< orphan*/ ) ; 

void print__rq_regs_st(struct display_mode_lib *mode_lib, display_rq_regs_st rq_regs)
{
	dml_print("DML_RQ_DLG_CALC: =====================================\n");
	dml_print("DML_RQ_DLG_CALC: DISPLAY_RQ_REGS_ST\n");
	dml_print("DML_RQ_DLG_CALC:  <LUMA>\n");
	print__data_rq_regs_st(mode_lib, rq_regs.rq_regs_l);
	dml_print("DML_RQ_DLG_CALC:  <CHROMA>\n");
	print__data_rq_regs_st(mode_lib, rq_regs.rq_regs_c);
	dml_print("DML_RQ_DLG_CALC:    drq_expansion_mode  = 0x%0x\n", rq_regs.drq_expansion_mode);
	dml_print("DML_RQ_DLG_CALC:    prq_expansion_mode  = 0x%0x\n", rq_regs.prq_expansion_mode);
	dml_print("DML_RQ_DLG_CALC:    mrq_expansion_mode  = 0x%0x\n", rq_regs.mrq_expansion_mode);
	dml_print("DML_RQ_DLG_CALC:    crq_expansion_mode  = 0x%0x\n", rq_regs.crq_expansion_mode);
	dml_print("DML_RQ_DLG_CALC:    plane1_base_address = 0x%0x\n", rq_regs.plane1_base_address);
	dml_print("DML_RQ_DLG_CALC: =====================================\n");
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct io_register {int dummy; } ;
struct TYPE_28__ {scalar_t__ gfx_chip_name; } ;
struct TYPE_27__ {int reg_num; struct io_register* reg; } ;
struct TYPE_26__ {int reg_num; struct io_register* reg; } ;
struct TYPE_25__ {int reg_num; struct io_register* reg; } ;
struct TYPE_24__ {int reg_num; struct io_register* reg; } ;
struct TYPE_23__ {int reg_num; struct io_register* reg; } ;
struct TYPE_22__ {int reg_num; struct io_register* reg; } ;
struct TYPE_21__ {int reg_num; struct io_register* reg; } ;
struct TYPE_20__ {int reg_num; struct io_register* reg; } ;
struct TYPE_19__ {TYPE_5__ iga2_fifo_depth_select_reg; TYPE_1__ iga1_fifo_depth_select_reg; } ;
struct TYPE_18__ {TYPE_8__ iga2_display_queue_expire_num_reg; TYPE_4__ iga1_display_queue_expire_num_reg; } ;
struct TYPE_17__ {TYPE_7__ iga2_fifo_high_threshold_select_reg; TYPE_3__ iga1_fifo_high_threshold_select_reg; } ;
struct TYPE_16__ {TYPE_6__ iga2_fifo_threshold_select_reg; TYPE_2__ iga1_fifo_threshold_select_reg; } ;
struct TYPE_15__ {TYPE_9__* chip_info; } ;

/* Variables and functions */
 int CN700_IGA1_DISPLAY_QUEUE_EXPIRE_NUM ; 
 int CN700_IGA1_FIFO_HIGH_THRESHOLD ; 
 int CN700_IGA1_FIFO_MAX_DEPTH ; 
 int CN700_IGA1_FIFO_THRESHOLD ; 
 int CN700_IGA2_DISPLAY_QUEUE_EXPIRE_NUM ; 
 int CN700_IGA2_FIFO_HIGH_THRESHOLD ; 
 int CN700_IGA2_FIFO_MAX_DEPTH ; 
 int CN700_IGA2_FIFO_THRESHOLD ; 
 int CX700_IGA1_DISPLAY_QUEUE_EXPIRE_NUM ; 
 int CX700_IGA1_FIFO_HIGH_THRESHOLD ; 
 int CX700_IGA1_FIFO_MAX_DEPTH ; 
 int CX700_IGA1_FIFO_THRESHOLD ; 
 int CX700_IGA2_DISPLAY_QUEUE_EXPIRE_NUM ; 
 int CX700_IGA2_FIFO_HIGH_THRESHOLD ; 
 int CX700_IGA2_FIFO_MAX_DEPTH ; 
 int CX700_IGA2_FIFO_THRESHOLD ; 
 int IGA1 ; 
 int IGA1_DISPLAY_QUEUE_EXPIRE_NUM_FORMULA (int) ; 
 int IGA1_FIFO_DEPTH_SELECT_FORMULA (int) ; 
 int IGA1_FIFO_HIGH_THRESHOLD_FORMULA (int) ; 
 int IGA1_FIFO_THRESHOLD_FORMULA (int) ; 
 int IGA2_DISPLAY_QUEUE_EXPIRE_NUM_FORMULA (int) ; 
 int IGA2_FIFO_DEPTH_SELECT_FORMULA (int) ; 
 int IGA2_FIFO_HIGH_THRESHOLD_FORMULA (int) ; 
 int IGA2_FIFO_THRESHOLD_FORMULA (int) ; 
 int K800_IGA1_DISPLAY_QUEUE_EXPIRE_NUM ; 
 int K800_IGA1_FIFO_HIGH_THRESHOLD ; 
 int K800_IGA1_FIFO_MAX_DEPTH ; 
 int K800_IGA1_FIFO_THRESHOLD ; 
 int K800_IGA2_DISPLAY_QUEUE_EXPIRE_NUM ; 
 int K800_IGA2_FIFO_HIGH_THRESHOLD ; 
 int K800_IGA2_FIFO_MAX_DEPTH ; 
 int K800_IGA2_FIFO_THRESHOLD ; 
 int K8M890_IGA1_DISPLAY_QUEUE_EXPIRE_NUM ; 
 int K8M890_IGA1_FIFO_HIGH_THRESHOLD ; 
 int K8M890_IGA1_FIFO_MAX_DEPTH ; 
 int K8M890_IGA1_FIFO_THRESHOLD ; 
 int K8M890_IGA2_DISPLAY_QUEUE_EXPIRE_NUM ; 
 int K8M890_IGA2_FIFO_HIGH_THRESHOLD ; 
 int K8M890_IGA2_FIFO_MAX_DEPTH ; 
 int K8M890_IGA2_FIFO_THRESHOLD ; 
 int P4M890_IGA1_DISPLAY_QUEUE_EXPIRE_NUM ; 
 int P4M890_IGA1_FIFO_HIGH_THRESHOLD ; 
 int P4M890_IGA1_FIFO_MAX_DEPTH ; 
 int P4M890_IGA1_FIFO_THRESHOLD ; 
 int P4M890_IGA2_DISPLAY_QUEUE_EXPIRE_NUM ; 
 int P4M890_IGA2_FIFO_HIGH_THRESHOLD ; 
 int P4M890_IGA2_FIFO_MAX_DEPTH ; 
 int P4M890_IGA2_FIFO_THRESHOLD ; 
 int P4M900_IGA1_DISPLAY_QUEUE_EXPIRE_NUM ; 
 int P4M900_IGA1_FIFO_HIGH_THRESHOLD ; 
 int P4M900_IGA1_FIFO_MAX_DEPTH ; 
 int P4M900_IGA1_FIFO_THRESHOLD ; 
 int P4M900_IGA2_DISPLAY_QUEUE_EXPIRE_NUM ; 
 int P4M900_IGA2_FIFO_HIGH_THRESHOLD ; 
 int P4M900_IGA2_FIFO_MAX_DEPTH ; 
 int P4M900_IGA2_FIFO_THRESHOLD ; 
 int P880_IGA1_DISPLAY_QUEUE_EXPIRE_NUM ; 
 int P880_IGA1_FIFO_HIGH_THRESHOLD ; 
 int P880_IGA1_FIFO_MAX_DEPTH ; 
 int P880_IGA1_FIFO_THRESHOLD ; 
 int P880_IGA2_DISPLAY_QUEUE_EXPIRE_NUM ; 
 int P880_IGA2_FIFO_HIGH_THRESHOLD ; 
 int P880_IGA2_FIFO_MAX_DEPTH ; 
 int P880_IGA2_FIFO_THRESHOLD ; 
 scalar_t__ UNICHROME_CN700 ; 
 scalar_t__ UNICHROME_CX700 ; 
 scalar_t__ UNICHROME_K800 ; 
 scalar_t__ UNICHROME_K8M890 ; 
 scalar_t__ UNICHROME_P4M890 ; 
 scalar_t__ UNICHROME_P4M900 ; 
 scalar_t__ UNICHROME_PM800 ; 
 scalar_t__ UNICHROME_VX800 ; 
 scalar_t__ UNICHROME_VX855 ; 
 scalar_t__ UNICHROME_VX900 ; 
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  VIASR ; 
 int VX800_IGA1_DISPLAY_QUEUE_EXPIRE_NUM ; 
 int VX800_IGA1_FIFO_HIGH_THRESHOLD ; 
 int VX800_IGA1_FIFO_MAX_DEPTH ; 
 int VX800_IGA1_FIFO_THRESHOLD ; 
 int VX800_IGA2_DISPLAY_QUEUE_EXPIRE_NUM ; 
 int VX800_IGA2_FIFO_HIGH_THRESHOLD ; 
 int VX800_IGA2_FIFO_MAX_DEPTH ; 
 int VX800_IGA2_FIFO_THRESHOLD ; 
 int VX855_IGA1_DISPLAY_QUEUE_EXPIRE_NUM ; 
 int VX855_IGA1_FIFO_HIGH_THRESHOLD ; 
 int VX855_IGA1_FIFO_MAX_DEPTH ; 
 int VX855_IGA1_FIFO_THRESHOLD ; 
 int VX855_IGA2_DISPLAY_QUEUE_EXPIRE_NUM ; 
 int VX855_IGA2_FIFO_HIGH_THRESHOLD ; 
 int VX855_IGA2_FIFO_MAX_DEPTH ; 
 int VX855_IGA2_FIFO_THRESHOLD ; 
 int VX900_IGA1_DISPLAY_QUEUE_EXPIRE_NUM ; 
 int VX900_IGA1_FIFO_HIGH_THRESHOLD ; 
 int VX900_IGA1_FIFO_MAX_DEPTH ; 
 int VX900_IGA1_FIFO_THRESHOLD ; 
 int VX900_IGA2_DISPLAY_QUEUE_EXPIRE_NUM ; 
 int VX900_IGA2_FIFO_HIGH_THRESHOLD ; 
 int VX900_IGA2_FIFO_MAX_DEPTH ; 
 int VX900_IGA2_FIFO_THRESHOLD ; 
 TYPE_14__ display_fifo_depth_reg ; 
 TYPE_13__ display_queue_expire_num_reg ; 
 TYPE_12__ fifo_high_threshold_select_reg ; 
 TYPE_11__ fifo_threshold_select_reg ; 
 int /*<<< orphan*/  viafb_load_reg (int,int,struct io_register*,int /*<<< orphan*/ ) ; 
 TYPE_10__* viaparinfo ; 

void viafb_load_FIFO_reg(int set_iga, int hor_active, int ver_active)
{
	int reg_value;
	int viafb_load_reg_num;
	struct io_register *reg = NULL;
	int iga1_fifo_max_depth = 0, iga1_fifo_threshold =
	    0, iga1_fifo_high_threshold = 0, iga1_display_queue_expire_num = 0;
	int iga2_fifo_max_depth = 0, iga2_fifo_threshold =
	    0, iga2_fifo_high_threshold = 0, iga2_display_queue_expire_num = 0;

	if (set_iga == IGA1) {
		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_K800) {
			iga1_fifo_max_depth = K800_IGA1_FIFO_MAX_DEPTH;
			iga1_fifo_threshold = K800_IGA1_FIFO_THRESHOLD;
			iga1_fifo_high_threshold =
			    K800_IGA1_FIFO_HIGH_THRESHOLD;
			/* If resolution > 1280x1024, expire length = 64, else
			   expire length = 128 */
			if ((hor_active > 1280) && (ver_active > 1024))
				iga1_display_queue_expire_num = 16;
			else
				iga1_display_queue_expire_num =
				    K800_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;

		}

		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_PM800) {
			iga1_fifo_max_depth = P880_IGA1_FIFO_MAX_DEPTH;
			iga1_fifo_threshold = P880_IGA1_FIFO_THRESHOLD;
			iga1_fifo_high_threshold =
			    P880_IGA1_FIFO_HIGH_THRESHOLD;
			iga1_display_queue_expire_num =
			    P880_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;

			/* If resolution > 1280x1024, expire length = 64, else
			   expire length = 128 */
			if ((hor_active > 1280) && (ver_active > 1024))
				iga1_display_queue_expire_num = 16;
			else
				iga1_display_queue_expire_num =
				    P880_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;
		}

		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CN700) {
			iga1_fifo_max_depth = CN700_IGA1_FIFO_MAX_DEPTH;
			iga1_fifo_threshold = CN700_IGA1_FIFO_THRESHOLD;
			iga1_fifo_high_threshold =
			    CN700_IGA1_FIFO_HIGH_THRESHOLD;

			/* If resolution > 1280x1024, expire length = 64,
			   else expire length = 128 */
			if ((hor_active > 1280) && (ver_active > 1024))
				iga1_display_queue_expire_num = 16;
			else
				iga1_display_queue_expire_num =
				    CN700_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;
		}

		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CX700) {
			iga1_fifo_max_depth = CX700_IGA1_FIFO_MAX_DEPTH;
			iga1_fifo_threshold = CX700_IGA1_FIFO_THRESHOLD;
			iga1_fifo_high_threshold =
			    CX700_IGA1_FIFO_HIGH_THRESHOLD;
			iga1_display_queue_expire_num =
			    CX700_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;
		}

		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_K8M890) {
			iga1_fifo_max_depth = K8M890_IGA1_FIFO_MAX_DEPTH;
			iga1_fifo_threshold = K8M890_IGA1_FIFO_THRESHOLD;
			iga1_fifo_high_threshold =
			    K8M890_IGA1_FIFO_HIGH_THRESHOLD;
			iga1_display_queue_expire_num =
			    K8M890_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;
		}

		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_P4M890) {
			iga1_fifo_max_depth = P4M890_IGA1_FIFO_MAX_DEPTH;
			iga1_fifo_threshold = P4M890_IGA1_FIFO_THRESHOLD;
			iga1_fifo_high_threshold =
			    P4M890_IGA1_FIFO_HIGH_THRESHOLD;
			iga1_display_queue_expire_num =
			    P4M890_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;
		}

		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_P4M900) {
			iga1_fifo_max_depth = P4M900_IGA1_FIFO_MAX_DEPTH;
			iga1_fifo_threshold = P4M900_IGA1_FIFO_THRESHOLD;
			iga1_fifo_high_threshold =
			    P4M900_IGA1_FIFO_HIGH_THRESHOLD;
			iga1_display_queue_expire_num =
			    P4M900_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;
		}

		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_VX800) {
			iga1_fifo_max_depth = VX800_IGA1_FIFO_MAX_DEPTH;
			iga1_fifo_threshold = VX800_IGA1_FIFO_THRESHOLD;
			iga1_fifo_high_threshold =
			    VX800_IGA1_FIFO_HIGH_THRESHOLD;
			iga1_display_queue_expire_num =
			    VX800_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;
		}

		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_VX855) {
			iga1_fifo_max_depth = VX855_IGA1_FIFO_MAX_DEPTH;
			iga1_fifo_threshold = VX855_IGA1_FIFO_THRESHOLD;
			iga1_fifo_high_threshold =
			    VX855_IGA1_FIFO_HIGH_THRESHOLD;
			iga1_display_queue_expire_num =
			    VX855_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;
		}

		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_VX900) {
			iga1_fifo_max_depth = VX900_IGA1_FIFO_MAX_DEPTH;
			iga1_fifo_threshold = VX900_IGA1_FIFO_THRESHOLD;
			iga1_fifo_high_threshold =
			    VX900_IGA1_FIFO_HIGH_THRESHOLD;
			iga1_display_queue_expire_num =
			    VX900_IGA1_DISPLAY_QUEUE_EXPIRE_NUM;
		}

		/* Set Display FIFO Depath Select */
		reg_value = IGA1_FIFO_DEPTH_SELECT_FORMULA(iga1_fifo_max_depth);
		viafb_load_reg_num =
		    display_fifo_depth_reg.iga1_fifo_depth_select_reg.reg_num;
		reg = display_fifo_depth_reg.iga1_fifo_depth_select_reg.reg;
		viafb_load_reg(reg_value, viafb_load_reg_num, reg, VIASR);

		/* Set Display FIFO Threshold Select */
		reg_value = IGA1_FIFO_THRESHOLD_FORMULA(iga1_fifo_threshold);
		viafb_load_reg_num =
		    fifo_threshold_select_reg.
		    iga1_fifo_threshold_select_reg.reg_num;
		reg =
		    fifo_threshold_select_reg.
		    iga1_fifo_threshold_select_reg.reg;
		viafb_load_reg(reg_value, viafb_load_reg_num, reg, VIASR);

		/* Set FIFO High Threshold Select */
		reg_value =
		    IGA1_FIFO_HIGH_THRESHOLD_FORMULA(iga1_fifo_high_threshold);
		viafb_load_reg_num =
		    fifo_high_threshold_select_reg.
		    iga1_fifo_high_threshold_select_reg.reg_num;
		reg =
		    fifo_high_threshold_select_reg.
		    iga1_fifo_high_threshold_select_reg.reg;
		viafb_load_reg(reg_value, viafb_load_reg_num, reg, VIASR);

		/* Set Display Queue Expire Num */
		reg_value =
		    IGA1_DISPLAY_QUEUE_EXPIRE_NUM_FORMULA
		    (iga1_display_queue_expire_num);
		viafb_load_reg_num =
		    display_queue_expire_num_reg.
		    iga1_display_queue_expire_num_reg.reg_num;
		reg =
		    display_queue_expire_num_reg.
		    iga1_display_queue_expire_num_reg.reg;
		viafb_load_reg(reg_value, viafb_load_reg_num, reg, VIASR);

	} else {
		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_K800) {
			iga2_fifo_max_depth = K800_IGA2_FIFO_MAX_DEPTH;
			iga2_fifo_threshold = K800_IGA2_FIFO_THRESHOLD;
			iga2_fifo_high_threshold =
			    K800_IGA2_FIFO_HIGH_THRESHOLD;

			/* If resolution > 1280x1024, expire length = 64,
			   else  expire length = 128 */
			if ((hor_active > 1280) && (ver_active > 1024))
				iga2_display_queue_expire_num = 16;
			else
				iga2_display_queue_expire_num =
				    K800_IGA2_DISPLAY_QUEUE_EXPIRE_NUM;
		}

		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_PM800) {
			iga2_fifo_max_depth = P880_IGA2_FIFO_MAX_DEPTH;
			iga2_fifo_threshold = P880_IGA2_FIFO_THRESHOLD;
			iga2_fifo_high_threshold =
			    P880_IGA2_FIFO_HIGH_THRESHOLD;

			/* If resolution > 1280x1024, expire length = 64,
			   else  expire length = 128 */
			if ((hor_active > 1280) && (ver_active > 1024))
				iga2_display_queue_expire_num = 16;
			else
				iga2_display_queue_expire_num =
				    P880_IGA2_DISPLAY_QUEUE_EXPIRE_NUM;
		}

		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CN700) {
			iga2_fifo_max_depth = CN700_IGA2_FIFO_MAX_DEPTH;
			iga2_fifo_threshold = CN700_IGA2_FIFO_THRESHOLD;
			iga2_fifo_high_threshold =
			    CN700_IGA2_FIFO_HIGH_THRESHOLD;

			/* If resolution > 1280x1024, expire length = 64,
			   else expire length = 128 */
			if ((hor_active > 1280) && (ver_active > 1024))
				iga2_display_queue_expire_num = 16;
			else
				iga2_display_queue_expire_num =
				    CN700_IGA2_DISPLAY_QUEUE_EXPIRE_NUM;
		}

		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CX700) {
			iga2_fifo_max_depth = CX700_IGA2_FIFO_MAX_DEPTH;
			iga2_fifo_threshold = CX700_IGA2_FIFO_THRESHOLD;
			iga2_fifo_high_threshold =
			    CX700_IGA2_FIFO_HIGH_THRESHOLD;
			iga2_display_queue_expire_num =
			    CX700_IGA2_DISPLAY_QUEUE_EXPIRE_NUM;
		}

		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_K8M890) {
			iga2_fifo_max_depth = K8M890_IGA2_FIFO_MAX_DEPTH;
			iga2_fifo_threshold = K8M890_IGA2_FIFO_THRESHOLD;
			iga2_fifo_high_threshold =
			    K8M890_IGA2_FIFO_HIGH_THRESHOLD;
			iga2_display_queue_expire_num =
			    K8M890_IGA2_DISPLAY_QUEUE_EXPIRE_NUM;
		}

		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_P4M890) {
			iga2_fifo_max_depth = P4M890_IGA2_FIFO_MAX_DEPTH;
			iga2_fifo_threshold = P4M890_IGA2_FIFO_THRESHOLD;
			iga2_fifo_high_threshold =
			    P4M890_IGA2_FIFO_HIGH_THRESHOLD;
			iga2_display_queue_expire_num =
			    P4M890_IGA2_DISPLAY_QUEUE_EXPIRE_NUM;
		}

		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_P4M900) {
			iga2_fifo_max_depth = P4M900_IGA2_FIFO_MAX_DEPTH;
			iga2_fifo_threshold = P4M900_IGA2_FIFO_THRESHOLD;
			iga2_fifo_high_threshold =
			    P4M900_IGA2_FIFO_HIGH_THRESHOLD;
			iga2_display_queue_expire_num =
			    P4M900_IGA2_DISPLAY_QUEUE_EXPIRE_NUM;
		}

		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_VX800) {
			iga2_fifo_max_depth = VX800_IGA2_FIFO_MAX_DEPTH;
			iga2_fifo_threshold = VX800_IGA2_FIFO_THRESHOLD;
			iga2_fifo_high_threshold =
			    VX800_IGA2_FIFO_HIGH_THRESHOLD;
			iga2_display_queue_expire_num =
			    VX800_IGA2_DISPLAY_QUEUE_EXPIRE_NUM;
		}

		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_VX855) {
			iga2_fifo_max_depth = VX855_IGA2_FIFO_MAX_DEPTH;
			iga2_fifo_threshold = VX855_IGA2_FIFO_THRESHOLD;
			iga2_fifo_high_threshold =
			    VX855_IGA2_FIFO_HIGH_THRESHOLD;
			iga2_display_queue_expire_num =
			    VX855_IGA2_DISPLAY_QUEUE_EXPIRE_NUM;
		}

		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_VX900) {
			iga2_fifo_max_depth = VX900_IGA2_FIFO_MAX_DEPTH;
			iga2_fifo_threshold = VX900_IGA2_FIFO_THRESHOLD;
			iga2_fifo_high_threshold =
			    VX900_IGA2_FIFO_HIGH_THRESHOLD;
			iga2_display_queue_expire_num =
			    VX900_IGA2_DISPLAY_QUEUE_EXPIRE_NUM;
		}

		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_K800) {
			/* Set Display FIFO Depath Select */
			reg_value =
			    IGA2_FIFO_DEPTH_SELECT_FORMULA(iga2_fifo_max_depth)
			    - 1;
			/* Patch LCD in IGA2 case */
			viafb_load_reg_num =
			    display_fifo_depth_reg.
			    iga2_fifo_depth_select_reg.reg_num;
			reg =
			    display_fifo_depth_reg.
			    iga2_fifo_depth_select_reg.reg;
			viafb_load_reg(reg_value,
				viafb_load_reg_num, reg, VIACR);
		} else {

			/* Set Display FIFO Depath Select */
			reg_value =
			    IGA2_FIFO_DEPTH_SELECT_FORMULA(iga2_fifo_max_depth);
			viafb_load_reg_num =
			    display_fifo_depth_reg.
			    iga2_fifo_depth_select_reg.reg_num;
			reg =
			    display_fifo_depth_reg.
			    iga2_fifo_depth_select_reg.reg;
			viafb_load_reg(reg_value,
				viafb_load_reg_num, reg, VIACR);
		}

		/* Set Display FIFO Threshold Select */
		reg_value = IGA2_FIFO_THRESHOLD_FORMULA(iga2_fifo_threshold);
		viafb_load_reg_num =
		    fifo_threshold_select_reg.
		    iga2_fifo_threshold_select_reg.reg_num;
		reg =
		    fifo_threshold_select_reg.
		    iga2_fifo_threshold_select_reg.reg;
		viafb_load_reg(reg_value, viafb_load_reg_num, reg, VIACR);

		/* Set FIFO High Threshold Select */
		reg_value =
		    IGA2_FIFO_HIGH_THRESHOLD_FORMULA(iga2_fifo_high_threshold);
		viafb_load_reg_num =
		    fifo_high_threshold_select_reg.
		    iga2_fifo_high_threshold_select_reg.reg_num;
		reg =
		    fifo_high_threshold_select_reg.
		    iga2_fifo_high_threshold_select_reg.reg;
		viafb_load_reg(reg_value, viafb_load_reg_num, reg, VIACR);

		/* Set Display Queue Expire Num */
		reg_value =
		    IGA2_DISPLAY_QUEUE_EXPIRE_NUM_FORMULA
		    (iga2_display_queue_expire_num);
		viafb_load_reg_num =
		    display_queue_expire_num_reg.
		    iga2_display_queue_expire_num_reg.reg_num;
		reg =
		    display_queue_expire_num_reg.
		    iga2_display_queue_expire_num_reg.reg;
		viafb_load_reg(reg_value, viafb_load_reg_num, reg, VIACR);

	}

}
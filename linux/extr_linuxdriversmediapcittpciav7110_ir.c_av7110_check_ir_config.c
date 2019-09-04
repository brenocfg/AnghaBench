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
struct TYPE_2__ {int protocol; int inversion; int ir_config; scalar_t__ device_mask; } ;
struct av7110 {TYPE_1__ ir; int /*<<< orphan*/  arm_app; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMTYPE_PIDFILTER ; 
 int ENODEV ; 
 int FW_VERSION (int /*<<< orphan*/ ) ; 
 int IR_RC5 ; 
 int IR_RC5_EXT ; 
 int IR_RCMM ; 
 int /*<<< orphan*/  SetIR ; 
 int av7110_fw_cmd (struct av7110*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int av_cnt ; 
 struct av7110** av_list ; 
 scalar_t__* ir_device_mask ; 
 int* ir_inversion ; 
 int* ir_protocol ; 

int av7110_check_ir_config(struct av7110 *av7110, int force)
{
	int i;
	int modified = force;
	int ret = -ENODEV;

	for (i = 0; i < av_cnt; i++)
		if (av7110 == av_list[i])
			break;

	if (i < av_cnt && av7110) {
		if ((av7110->ir.protocol & 1) != ir_protocol[i] ||
		    av7110->ir.inversion != ir_inversion[i])
			modified = true;

		if (modified) {
			/* protocol */
			if (ir_protocol[i]) {
				ir_protocol[i] = 1;
				av7110->ir.protocol = IR_RCMM;
				av7110->ir.ir_config = 0x0001;
			} else if (FW_VERSION(av7110->arm_app) >= 0x2620) {
				av7110->ir.protocol = IR_RC5_EXT;
				av7110->ir.ir_config = 0x0002;
			} else {
				av7110->ir.protocol = IR_RC5;
				av7110->ir.ir_config = 0x0000;
			}
			/* inversion */
			if (ir_inversion[i]) {
				ir_inversion[i] = 1;
				av7110->ir.ir_config |= 0x8000;
			}
			av7110->ir.inversion = ir_inversion[i];
			/* update ARM */
			ret = av7110_fw_cmd(av7110, COMTYPE_PIDFILTER, SetIR, 1,
						av7110->ir.ir_config);
		} else
			ret = 0;

		/* address */
		if (av7110->ir.device_mask != ir_device_mask[i])
			av7110->ir.device_mask = ir_device_mask[i];
	}

	return ret;
}
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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct rc_dev {struct av7110* priv; } ;
struct TYPE_2__ {scalar_t__ ir_config; } ;
struct av7110 {TYPE_1__ ir; int /*<<< orphan*/  arm_app; } ;

/* Variables and functions */
 int EINVAL ; 
 int FW_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ IR_RC5 ; 
 scalar_t__ IR_RC5_EXT ; 
 scalar_t__ IR_RCMM ; 
 int RC_PROTO_BIT_RC5 ; 
 int RC_PROTO_BIT_RCMM32 ; 
 int av7110_set_ir_config (struct av7110*) ; 

__attribute__((used)) static int change_protocol(struct rc_dev *rcdev, u64 *rc_type)
{
	struct av7110 *av7110 = rcdev->priv;
	u32 ir_config;

	if (*rc_type & RC_PROTO_BIT_RCMM32) {
		ir_config = IR_RCMM;
		*rc_type = RC_PROTO_BIT_RCMM32;
	} else if (*rc_type & RC_PROTO_BIT_RC5) {
		if (FW_VERSION(av7110->arm_app) >= 0x2620)
			ir_config = IR_RC5_EXT;
		else
			ir_config = IR_RC5;
		*rc_type = RC_PROTO_BIT_RC5;
	} else {
		return -EINVAL;
	}

	if (ir_config == av7110->ir.ir_config)
		return 0;

	av7110->ir.ir_config = ir_config;

	return av7110_set_ir_config(av7110);
}
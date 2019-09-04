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
typedef  int u8 ;
struct em28xx_ir_poll_result {int toggle_bit; int read_count; int scancode; int /*<<< orphan*/  protocol; } ;
struct em28xx_IR {int rc_proto; struct em28xx* dev; } ;
struct em28xx {int (* em28xx_read_reg_req_len ) (struct em28xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ;} ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  EM28XX_R45_IR ; 
#define  RC_PROTO_BIT_NEC 129 
#define  RC_PROTO_BIT_RC5 128 
 int /*<<< orphan*/  RC_PROTO_NEC ; 
 int /*<<< orphan*/  RC_PROTO_RC5 ; 
 int /*<<< orphan*/  RC_PROTO_UNKNOWN ; 
 int RC_SCANCODE_NEC (int,int) ; 
 int RC_SCANCODE_RC5 (int,int) ; 
 int stub1 (struct em28xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int default_polling_getkey(struct em28xx_IR *ir,
				  struct em28xx_ir_poll_result *poll_result)
{
	struct em28xx *dev = ir->dev;
	int rc;
	u8 msg[3] = { 0, 0, 0 };

	/*
	 * Read key toggle, brand, and key code
	 * on registers 0x45, 0x46 and 0x47
	 */
	rc = dev->em28xx_read_reg_req_len(dev, 0, EM28XX_R45_IR,
					  msg, sizeof(msg));
	if (rc < 0)
		return rc;

	/* Infrared toggle (Reg 0x45[7]) */
	poll_result->toggle_bit = (msg[0] >> 7);

	/* Infrared read count (Reg 0x45[6:0] */
	poll_result->read_count = (msg[0] & 0x7f);

	/* Remote Control Address/Data (Regs 0x46/0x47) */
	switch (ir->rc_proto) {
	case RC_PROTO_BIT_RC5:
		poll_result->protocol = RC_PROTO_RC5;
		poll_result->scancode = RC_SCANCODE_RC5(msg[1], msg[2]);
		break;

	case RC_PROTO_BIT_NEC:
		poll_result->protocol = RC_PROTO_NEC;
		poll_result->scancode = RC_SCANCODE_NEC(msg[1], msg[2]);
		break;

	default:
		poll_result->protocol = RC_PROTO_UNKNOWN;
		poll_result->scancode = msg[1] << 8 | msg[2];
		break;
	}

	return 0;
}
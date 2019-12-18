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
typedef  int u64 ;
struct img_ir_scancode_req {unsigned int scancode; int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 int EINVAL ; 
 int IMG_IR_REPEATCODE ; 
 int IMG_IR_SCANCODE ; 
 int /*<<< orphan*/  RC_PROTO_SANYO ; 

__attribute__((used)) static int img_ir_sanyo_scancode(int len, u64 raw, u64 enabled_protocols,
				 struct img_ir_scancode_req *request)
{
	unsigned int addr, addr_inv, data, data_inv;
	/* a repeat code has no data */
	if (!len)
		return IMG_IR_REPEATCODE;
	if (len != 42)
		return -EINVAL;
	addr     = (raw >>  0) & 0x1fff;
	addr_inv = (raw >> 13) & 0x1fff;
	data     = (raw >> 26) & 0xff;
	data_inv = (raw >> 34) & 0xff;
	/* Validate data */
	if ((data_inv ^ data) != 0xff)
		return -EINVAL;
	/* Validate address */
	if ((addr_inv ^ addr) != 0x1fff)
		return -EINVAL;

	/* Normal Sanyo */
	request->protocol = RC_PROTO_SANYO;
	request->scancode = addr << 8 | data;
	return IMG_IR_SCANCODE;
}
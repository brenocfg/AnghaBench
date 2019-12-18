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
 int IMG_IR_SCANCODE ; 
 int /*<<< orphan*/  RC_PROTO_JVC ; 

__attribute__((used)) static int img_ir_jvc_scancode(int len, u64 raw, u64 enabled_protocols,
			       struct img_ir_scancode_req *request)
{
	unsigned int cust, data;

	if (len != 16)
		return -EINVAL;

	cust = (raw >> 0) & 0xff;
	data = (raw >> 8) & 0xff;

	request->protocol = RC_PROTO_JVC;
	request->scancode = cust << 8 | data;
	return IMG_IR_SCANCODE;
}
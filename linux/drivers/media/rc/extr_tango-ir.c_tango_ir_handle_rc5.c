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
typedef  int u32 ;
struct tango_ir {int /*<<< orphan*/  rc; scalar_t__ rc5_base; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ IR_RC5_DATA ; 
 int /*<<< orphan*/  RC_PROTO_RC5 ; 
 int RC_SCANCODE_RC5 (int,int) ; 
 int /*<<< orphan*/  rc_keydown (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static void tango_ir_handle_rc5(struct tango_ir *ir)
{
	u32 data, field, toggle, addr, cmd, code;

	data = readl_relaxed(ir->rc5_base + IR_RC5_DATA);
	if (data & BIT(31))
		return;

	field = data >> 12 & 1;
	toggle = data >> 11 & 1;
	addr = data >> 6 & 0x1f;
	cmd = (data & 0x3f) | (field ^ 1) << 6;

	code = RC_SCANCODE_RC5(addr, cmd);
	rc_keydown(ir->rc, RC_PROTO_RC5, code, toggle);
}
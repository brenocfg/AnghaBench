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
struct tango_ir {int /*<<< orphan*/  rc; scalar_t__ rc6_base; } ;

/* Variables and functions */
 scalar_t__ RC6_DATA0 ; 
 scalar_t__ RC6_DATA1 ; 
 int /*<<< orphan*/  RC_PROTO_RC6_0 ; 
 int RC_SCANCODE_RC6_0 (int,int) ; 
 int /*<<< orphan*/  rc_keydown (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static void tango_ir_handle_rc6(struct tango_ir *ir)
{
	u32 data0, data1, toggle, mode, addr, cmd, code;

	data0 = readl_relaxed(ir->rc6_base + RC6_DATA0);
	data1 = readl_relaxed(ir->rc6_base + RC6_DATA1);

	mode = data0 >> 1 & 7;
	if (mode != 0)
		return;

	toggle = data0 & 1;
	addr = data0 >> 16;
	cmd = data1;

	code = RC_SCANCODE_RC6_0(addr, cmd);
	rc_keydown(ir->rc, RC_PROTO_RC6_0, code, toggle);
}
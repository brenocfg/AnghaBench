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
typedef  enum rc_proto { ____Placeholder_rc_proto } rc_proto ;

/* Variables and functions */
 scalar_t__ IR_NEC_DATA ; 
 int ir_nec_bytes_to_scancode (int,int,int,int,int*) ; 
 int /*<<< orphan*/  rc_keydown (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_repeat (int /*<<< orphan*/ ) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static void tango_ir_handle_nec(struct tango_ir *ir)
{
	u32 v, code;
	enum rc_proto proto;

	v = readl_relaxed(ir->rc5_base + IR_NEC_DATA);
	if (!v) {
		rc_repeat(ir->rc);
		return;
	}

	code = ir_nec_bytes_to_scancode(v, v >> 8, v >> 16, v >> 24, &proto);
	rc_keydown(ir->rc, proto, code, 0);
}
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
typedef  int u32 ;
struct timer_list {int dummy; } ;
struct bttv_ir {int active; int last_bit; int code; int shift_by; int /*<<< orphan*/  dev; int /*<<< orphan*/  base_time; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int RC5_ADDR (int) ; 
 int RC5_INSTR (int) ; 
 int RC5_START (int) ; 
 int RC5_TOGGLE (int) ; 
 int /*<<< orphan*/  RC_PROTO_RC5 ; 
 int RC_SCANCODE_RC5 (int,int) ; 
 int USEC_PER_SEC ; 
 int bttv_rc5_decode (int) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 struct bttv_ir* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct bttv_ir* ir ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_keydown (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void bttv_rc5_timer_end(struct timer_list *t)
{
	struct bttv_ir *ir = from_timer(ir, t, timer);
	ktime_t tv;
	u32 gap, rc5, scancode;
	u8 toggle, command, system;

	/* get time */
	tv = ktime_get();

	gap = ktime_to_us(ktime_sub(tv, ir->base_time));
	/* avoid overflow with gap >1s */
	if (gap > USEC_PER_SEC) {
		gap = 200000;
	}
	/* signal we're ready to start a new code */
	ir->active = false;

	/* Allow some timer jitter (RC5 is ~24ms anyway so this is ok) */
	if (gap < 28000) {
		dprintk("spurious timer_end\n");
		return;
	}

	if (ir->last_bit < 20) {
		/* ignore spurious codes (caused by light/other remotes) */
		dprintk("short code: %x\n", ir->code);
		return;
	}

	ir->code = (ir->code << ir->shift_by) | 1;
	rc5 = bttv_rc5_decode(ir->code);

	toggle = RC5_TOGGLE(rc5);
	system = RC5_ADDR(rc5);
	command = RC5_INSTR(rc5);

	switch (RC5_START(rc5)) {
	case 0x3:
		break;
	case 0x2:
		command += 0x40;
		break;
	default:
		return;
	}

	scancode = RC_SCANCODE_RC5(system, command);
	rc_keydown(ir->dev, RC_PROTO_RC5, scancode, toggle);
	dprintk("scancode %x, toggle %x\n", scancode, toggle);
}
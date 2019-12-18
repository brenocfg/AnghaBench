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
struct ir_raw_event {int dummy; } ;
typedef  enum rc_proto { ____Placeholder_rc_proto } rc_proto ;

/* Variables and functions */
 unsigned int CHECK_RC5X_NBITS ; 
 int EINVAL ; 
 unsigned int RC5X_NBITS ; 
 int RC5_NBITS ; 
 int RC5_SZ_NBITS ; 
 int RC_PROTO_RC5 ; 
 int RC_PROTO_RC5X_20 ; 
 int RC_PROTO_RC5_SZ ; 
 int ir_raw_gen_manchester (struct ir_raw_event**,unsigned int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ir_rc5_sz_timings ; 
 int /*<<< orphan*/  ir_rc5_timings ; 
 int /*<<< orphan*/ * ir_rc5x_timings ; 

__attribute__((used)) static int ir_rc5_encode(enum rc_proto protocol, u32 scancode,
			 struct ir_raw_event *events, unsigned int max)
{
	int ret;
	struct ir_raw_event *e = events;
	unsigned int data, xdata, command, commandx, system, pre_space_data;

	/* Detect protocol and convert scancode to raw data */
	if (protocol == RC_PROTO_RC5) {
		/* decode scancode */
		command  = (scancode & 0x003f) >> 0;
		commandx = (scancode & 0x0040) >> 6;
		system   = (scancode & 0x1f00) >> 8;
		/* encode data */
		data = !commandx << 12 | system << 6 | command;

		/* First bit is encoded by leader_pulse */
		ret = ir_raw_gen_manchester(&e, max, &ir_rc5_timings,
					    RC5_NBITS - 1, data);
		if (ret < 0)
			return ret;
	} else if (protocol == RC_PROTO_RC5X_20) {
		/* decode scancode */
		xdata    = (scancode & 0x00003f) >> 0;
		command  = (scancode & 0x003f00) >> 8;
		commandx = !(scancode & 0x004000);
		system   = (scancode & 0x1f0000) >> 16;

		/* encode data */
		data = commandx << 18 | system << 12 | command << 6 | xdata;

		/* First bit is encoded by leader_pulse */
		pre_space_data = data >> (RC5X_NBITS - CHECK_RC5X_NBITS);
		ret = ir_raw_gen_manchester(&e, max, &ir_rc5x_timings[0],
					    CHECK_RC5X_NBITS - 1,
					    pre_space_data);
		if (ret < 0)
			return ret;
		ret = ir_raw_gen_manchester(&e, max - (e - events),
					    &ir_rc5x_timings[1],
					    RC5X_NBITS - CHECK_RC5X_NBITS,
					    data);
		if (ret < 0)
			return ret;
	} else if (protocol == RC_PROTO_RC5_SZ) {
		/* RC5-SZ scancode is raw enough for Manchester as it is */
		/* First bit is encoded by leader_pulse */
		ret = ir_raw_gen_manchester(&e, max, &ir_rc5_sz_timings,
					    RC5_SZ_NBITS - 1,
					    scancode & 0x2fff);
		if (ret < 0)
			return ret;
	} else {
		return -EINVAL;
	}

	return e - events;
}
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
 int RC_PROTO_SONY12 ; 
 int RC_PROTO_SONY15 ; 
 int ir_raw_gen_pl (struct ir_raw_event**,unsigned int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ir_sony_timings ; 

__attribute__((used)) static int ir_sony_encode(enum rc_proto protocol, u32 scancode,
			  struct ir_raw_event *events, unsigned int max)
{
	struct ir_raw_event *e = events;
	u32 raw, len;
	int ret;

	if (protocol == RC_PROTO_SONY12) {
		raw = (scancode & 0x7f) | ((scancode & 0x1f0000) >> 9);
		len = 12;
	} else if (protocol == RC_PROTO_SONY15) {
		raw = (scancode & 0x7f) | ((scancode & 0xff0000) >> 9);
		len = 15;
	} else {
		raw = (scancode & 0x7f) | ((scancode & 0x1f0000) >> 9) |
		       ((scancode & 0xff00) << 4);
		len = 20;
	}

	ret = ir_raw_gen_pl(&e, max, &ir_sony_timings, len, raw);
	if (ret < 0)
		return ret;

	return e - events;
}
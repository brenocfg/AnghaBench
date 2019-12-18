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
 int EINVAL ; 
 int RC6_0_NBITS ; 
 int RC6_HEADER_NBITS ; 
 int RC_PROTO_RC6_0 ; 
#define  RC_PROTO_RC6_6A_20 131 
#define  RC_PROTO_RC6_6A_24 130 
#define  RC_PROTO_RC6_6A_32 129 
#define  RC_PROTO_RC6_MCE 128 
 int ir_raw_gen_manchester (struct ir_raw_event**,unsigned int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * ir_rc6_timings ; 

__attribute__((used)) static int ir_rc6_encode(enum rc_proto protocol, u32 scancode,
			 struct ir_raw_event *events, unsigned int max)
{
	int ret;
	struct ir_raw_event *e = events;

	if (protocol == RC_PROTO_RC6_0) {
		/* Modulate the header (Start Bit & Mode-0) */
		ret = ir_raw_gen_manchester(&e, max - (e - events),
					    &ir_rc6_timings[0],
					    RC6_HEADER_NBITS, (1 << 3));
		if (ret < 0)
			return ret;

		/* Modulate Trailer Bit */
		ret = ir_raw_gen_manchester(&e, max - (e - events),
					    &ir_rc6_timings[1], 1, 0);
		if (ret < 0)
			return ret;

		/* Modulate rest of the data */
		ret = ir_raw_gen_manchester(&e, max - (e - events),
					    &ir_rc6_timings[2], RC6_0_NBITS,
					    scancode);
		if (ret < 0)
			return ret;

	} else {
		int bits;

		switch (protocol) {
		case RC_PROTO_RC6_MCE:
		case RC_PROTO_RC6_6A_32:
			bits = 32;
			break;
		case RC_PROTO_RC6_6A_24:
			bits = 24;
			break;
		case RC_PROTO_RC6_6A_20:
			bits = 20;
			break;
		default:
			return -EINVAL;
		}

		/* Modulate the header (Start Bit & Header-version 6 */
		ret = ir_raw_gen_manchester(&e, max - (e - events),
					    &ir_rc6_timings[0],
					    RC6_HEADER_NBITS, (1 << 3 | 6));
		if (ret < 0)
			return ret;

		/* Modulate Trailer Bit */
		ret = ir_raw_gen_manchester(&e, max - (e - events),
					    &ir_rc6_timings[1], 1, 0);
		if (ret < 0)
			return ret;

		/* Modulate rest of the data */
		ret = ir_raw_gen_manchester(&e, max - (e - events),
					    &ir_rc6_timings[2],
					    bits,
					    scancode);
		if (ret < 0)
			return ret;
	}

	return e - events;
}
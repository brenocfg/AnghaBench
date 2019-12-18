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
typedef  int /*<<< orphan*/  u32 ;
struct ir_raw_event {int dummy; } ;
typedef  enum rc_proto { ____Placeholder_rc_proto } rc_proto ;

/* Variables and functions */
 int /*<<< orphan*/  NEC_NBITS ; 
 int /*<<< orphan*/  ir_nec_scancode_to_raw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_nec_timings ; 
 int ir_raw_gen_pd (struct ir_raw_event**,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ir_nec_encode(enum rc_proto protocol, u32 scancode,
			 struct ir_raw_event *events, unsigned int max)
{
	struct ir_raw_event *e = events;
	int ret;
	u32 raw;

	/* Convert a NEC scancode to raw NEC data */
	raw = ir_nec_scancode_to_raw(protocol, scancode);

	/* Modulate the raw data using a pulse distance modulation */
	ret = ir_raw_gen_pd(&e, max, &ir_nec_timings, NEC_NBITS, raw);
	if (ret < 0)
		return ret;

	return e - events;
}
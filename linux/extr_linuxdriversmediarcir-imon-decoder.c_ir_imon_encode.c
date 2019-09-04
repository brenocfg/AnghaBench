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
struct ir_raw_event {int pulse; int /*<<< orphan*/  duration; } ;
typedef  enum rc_proto { ____Placeholder_rc_proto } rc_proto ;

/* Variables and functions */
 int BIT (int) ; 
 int ENOBUFS ; 
 int IMON_BITS ; 
 int IMON_CHKBITS ; 
 scalar_t__ IMON_UNIT ; 
 int /*<<< orphan*/  init_ir_raw_event_duration (struct ir_raw_event*,int,scalar_t__) ; 

__attribute__((used)) static int ir_imon_encode(enum rc_proto protocol, u32 scancode,
			  struct ir_raw_event *events, unsigned int max)
{
	struct ir_raw_event *e = events;
	int i, pulse;

	if (!max--)
		return -ENOBUFS;
	init_ir_raw_event_duration(e, 1, IMON_UNIT);

	for (i = IMON_BITS; i >= 0; i--) {
		if (BIT(i) & IMON_CHKBITS)
			pulse = !(scancode & (BIT(i) | BIT(i + 1)));
		else
			pulse = 0;

		if (pulse == e->pulse) {
			e->duration += IMON_UNIT;
		} else {
			if (!max--)
				return -ENOBUFS;
			init_ir_raw_event_duration(++e, pulse, IMON_UNIT);
		}

		pulse = !(scancode & BIT(i));

		if (pulse == e->pulse) {
			e->duration += IMON_UNIT;
		} else {
			if (!max--)
				return -ENOBUFS;
			init_ir_raw_event_duration(++e, pulse, IMON_UNIT);
		}
	}

	if (e->pulse)
		e++;

	return e - events;
}
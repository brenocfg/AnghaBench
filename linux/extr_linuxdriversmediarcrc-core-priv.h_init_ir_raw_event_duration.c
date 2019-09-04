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
struct ir_raw_event {unsigned int pulse; int /*<<< orphan*/  duration; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_ir_raw_event (struct ir_raw_event*) ; 

__attribute__((used)) static inline void init_ir_raw_event_duration(struct ir_raw_event *ev,
					      unsigned int pulse,
					      u32 duration)
{
	init_ir_raw_event(ev);
	ev->duration = duration;
	ev->pulse = pulse;
}
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
struct allegro_channel {int state; } ;
typedef  enum allegro_state { ____Placeholder_allegro_state } allegro_state ;

/* Variables and functions */

__attribute__((used)) static inline int
allegro_set_state(struct allegro_channel *channel, enum allegro_state state)
{
	channel->state = state;

	return 0;
}
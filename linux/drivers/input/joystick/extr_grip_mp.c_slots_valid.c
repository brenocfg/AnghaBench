#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct grip_mp {TYPE_1__** port; } ;
struct TYPE_2__ {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ GRIP_MODE_NONE ; 
 scalar_t__ GRIP_MODE_RESET ; 
 int IO_DONE ; 
 int IO_GOT_PACKET ; 
 int get_and_decode_packet (struct grip_mp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int slots_valid(struct grip_mp *grip)
{
	int flags, slot, invalid = 0, active = 0;

	flags = get_and_decode_packet(grip, 0);
	if (!(flags & IO_GOT_PACKET))
		return 0;

	for (slot = 0; slot < 4; slot++) {
		if (grip->port[slot]->mode == GRIP_MODE_RESET)
			invalid = 1;
		if (grip->port[slot]->mode != GRIP_MODE_NONE)
			active = 1;
	}

	/* Return true if no active slot but multiport sent all its data */
	if (!active)
		return (flags & IO_DONE) ? 1 : 0;

	/* Return false if invalid device code received */
	return invalid ? 0 : 1;
}
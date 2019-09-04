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
struct gameport {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  GRIP_INIT_DELAY ; 
 int IO_MODE_FAST ; 
 int /*<<< orphan*/  IO_RESET ; 
 int IO_RETRY ; 
 int /*<<< orphan*/  gameport_trigger (struct gameport*) ; 
 scalar_t__* init_seq ; 
 int multiport_io (struct gameport*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dig_mode_start(struct gameport *gameport, u32 *packet)
{
	int i;
	int flags, tries = 0, bads = 0;

	for (i = 0; i < ARRAY_SIZE(init_seq); i++) {     /* Send magic sequence */
		if (init_seq[i])
			gameport_trigger(gameport);
		udelay(GRIP_INIT_DELAY);
	}

	for (i = 0; i < 16; i++)            /* Wait for multiport to settle */
		udelay(GRIP_INIT_DELAY);

	while (tries < 64 && bads < 8) {    /* Reset multiport and try getting a packet */

		flags = multiport_io(gameport, IO_RESET, 0x27, packet);

		if (flags & IO_MODE_FAST)
			return 1;

		if (flags & IO_RETRY)
			tries++;
		else
			bads++;
	}
	return 0;
}
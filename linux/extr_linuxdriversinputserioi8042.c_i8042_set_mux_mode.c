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

/* Variables and functions */
 int /*<<< orphan*/  I8042_CMD_AUX_LOOP ; 
 scalar_t__ i8042_command (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i8042_flush () ; 

__attribute__((used)) static int i8042_set_mux_mode(bool multiplex, unsigned char *mux_version)
{

	unsigned char param, val;
/*
 * Get rid of bytes in the queue.
 */

	i8042_flush();

/*
 * Internal loopback test - send three bytes, they should come back from the
 * mouse interface, the last should be version.
 */

	param = val = 0xf0;
	if (i8042_command(&param, I8042_CMD_AUX_LOOP) || param != val)
		return -1;
	param = val = multiplex ? 0x56 : 0xf6;
	if (i8042_command(&param, I8042_CMD_AUX_LOOP) || param != val)
		return -1;
	param = val = multiplex ? 0xa4 : 0xa5;
	if (i8042_command(&param, I8042_CMD_AUX_LOOP) || param == val)
		return -1;

/*
 * Workaround for interference with USB Legacy emulation
 * that causes a v10.12 MUX to be found.
 */
	if (param == 0xac)
		return -1;

	if (mux_version)
		*mux_version = param;

	return 0;
}
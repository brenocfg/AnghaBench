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
typedef  scalar_t__ u8 ;
struct mipi_dbi {scalar_t__* read_commands; } ;

/* Variables and functions */

__attribute__((used)) static bool mipi_dbi_command_is_read(struct mipi_dbi *mipi, u8 cmd)
{
	unsigned int i;

	if (!mipi->read_commands)
		return false;

	for (i = 0; i < 0xff; i++) {
		if (!mipi->read_commands[i])
			return false;
		if (cmd == mipi->read_commands[i])
			return true;
	}

	return false;
}
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
struct steam_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STEAM_CMD_CLEAR_MAPPINGS ; 
 int /*<<< orphan*/  STEAM_CMD_DEFAULT_MAPPINGS ; 
 int /*<<< orphan*/  STEAM_CMD_DEFAULT_MOUSE ; 
 int /*<<< orphan*/  STEAM_REG_RPAD_MARGIN ; 
 int /*<<< orphan*/  STEAM_REG_RPAD_MODE ; 
 int /*<<< orphan*/  steam_send_report_byte (struct steam_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  steam_write_registers (struct steam_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void steam_set_lizard_mode(struct steam_device *steam, bool enable)
{
	if (enable) {
		/* enable esc, enter, cursors */
		steam_send_report_byte(steam, STEAM_CMD_DEFAULT_MAPPINGS);
		/* enable mouse */
		steam_send_report_byte(steam, STEAM_CMD_DEFAULT_MOUSE);
		steam_write_registers(steam,
			STEAM_REG_RPAD_MARGIN, 0x01, /* enable margin */
			0);
	} else {
		/* disable esc, enter, cursor */
		steam_send_report_byte(steam, STEAM_CMD_CLEAR_MAPPINGS);
		steam_write_registers(steam,
			STEAM_REG_RPAD_MODE, 0x07, /* disable mouse */
			STEAM_REG_RPAD_MARGIN, 0x00, /* disable margin */
			0);
	}
}
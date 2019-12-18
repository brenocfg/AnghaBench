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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct acx565akm_panel {unsigned int cabc_mode; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPID_CMD_READ_CABC ; 
 int /*<<< orphan*/  MIPID_CMD_WRITE_CABC ; 
 int /*<<< orphan*/  acx565akm_read (struct acx565akm_panel*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  acx565akm_write (struct acx565akm_panel*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void acx565akm_set_cabc_mode(struct acx565akm_panel *lcd,
				    unsigned int mode)
{
	u16 cabc_ctrl;

	lcd->cabc_mode = mode;
	if (!lcd->enabled)
		return;
	cabc_ctrl = 0;
	acx565akm_read(lcd, MIPID_CMD_READ_CABC, (u8 *)&cabc_ctrl, 1);
	cabc_ctrl &= ~3;
	cabc_ctrl |= (1 << 8) | (mode & 3);
	acx565akm_write(lcd, MIPID_CMD_WRITE_CABC, (u8 *)&cabc_ctrl, 2);
}
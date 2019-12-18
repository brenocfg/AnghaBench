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
struct scsi_tape {int dummy; } ;
typedef  unsigned char s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ST_DEB_MSG ; 
 int /*<<< orphan*/  debugging ; 
 int /*<<< orphan*/  st_printk (int /*<<< orphan*/ ,struct scsi_tape*,char*,char*,unsigned char,char*) ; 

__attribute__((used)) static void deb_space_print(struct scsi_tape *STp, int direction, char *units, unsigned char *cmd)
{
	s32 sc;

	if (!debugging)
		return;

	sc = cmd[2] & 0x80 ? 0xff000000 : 0;
	sc |= (cmd[2] << 16) | (cmd[3] << 8) | cmd[4];
	if (direction)
		sc = -sc;
	st_printk(ST_DEB_MSG, STp, "Spacing tape %s over %d %s.\n",
		  direction ? "backward" : "forward", sc, units);
}
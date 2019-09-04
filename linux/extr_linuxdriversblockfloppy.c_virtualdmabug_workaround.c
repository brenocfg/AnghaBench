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
struct TYPE_2__ {int length; } ;

/* Variables and functions */
 int COMMAND ; 
 scalar_t__ CT (int) ; 
 scalar_t__ FD_WRITE ; 
 int SECTOR ; 
 int SECT_PER_TRACK ; 
 int SIZECODE ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 
 TYPE_1__* raw_cmd ; 

__attribute__((used)) static void virtualdmabug_workaround(void)
{
	int hard_sectors;
	int end_sector;

	if (CT(COMMAND) == FD_WRITE) {
		COMMAND &= ~0x80;	/* switch off multiple track mode */

		hard_sectors = raw_cmd->length >> (7 + SIZECODE);
		end_sector = SECTOR + hard_sectors - 1;
		if (end_sector > SECT_PER_TRACK) {
			pr_info("too many sectors %d > %d\n",
				end_sector, SECT_PER_TRACK);
			return;
		}
		SECT_PER_TRACK = end_sector;
					/* make sure SECT_PER_TRACK
					 * points to end of transfer */
	}
}
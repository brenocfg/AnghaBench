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
struct pg {int drive; int /*<<< orphan*/  name; int /*<<< orphan*/ * bufptr; scalar_t__ present; scalar_t__ busy; int /*<<< orphan*/  access; int /*<<< orphan*/  pia; int /*<<< orphan*/ * pi; } ;

/* Variables and functions */
 size_t D_PRT ; 
 size_t D_SLV ; 
 int /*<<< orphan*/  PG_NAMELEN ; 
 int PG_UNITS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pg* devices ; 
 int*** drives ; 
 char* name ; 
 scalar_t__ pg_drive_count ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char) ; 

__attribute__((used)) static void pg_init_units(void)
{
	int unit;

	pg_drive_count = 0;
	for (unit = 0; unit < PG_UNITS; unit++) {
		int *parm = *drives[unit];
		struct pg *dev = &devices[unit];
		dev->pi = &dev->pia;
		clear_bit(0, &dev->access);
		dev->busy = 0;
		dev->present = 0;
		dev->bufptr = NULL;
		dev->drive = parm[D_SLV];
		snprintf(dev->name, PG_NAMELEN, "%s%c", name, 'a'+unit);
		if (parm[D_PRT])
			pg_drive_count++;
	}
}
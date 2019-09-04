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
struct TYPE_2__ {int /*<<< orphan*/  mask; } ;
struct pcd_unit {TYPE_1__ info; int /*<<< orphan*/  present; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_CD_R ; 
 int /*<<< orphan*/  CDC_CD_RW ; 
 int /*<<< orphan*/  CDC_CLOSE_TRAY ; 
 int /*<<< orphan*/  CDC_LOCK ; 
 int /*<<< orphan*/  CDC_OPEN_TRAY ; 
 int /*<<< orphan*/  CDC_PLAY_AUDIO ; 
 int PCD_UNITS ; 
 struct pcd_unit* pcd ; 
 int pcd_atapi (struct pcd_unit*,char*,int,char*,char*) ; 

__attribute__((used)) static void pcd_probe_capabilities(void)
{
	int unit, r;
	char buffer[32];
	char cmd[12] = { 0x5a, 1 << 3, 0x2a, 0, 0, 0, 0, 18, 0, 0, 0, 0 };
	struct pcd_unit *cd;

	for (unit = 0, cd = pcd; unit < PCD_UNITS; unit++, cd++) {
		if (!cd->present)
			continue;
		r = pcd_atapi(cd, cmd, 18, buffer, "mode sense capabilities");
		if (r)
			continue;
		/* we should now have the cap page */
		if ((buffer[11] & 1) == 0)
			cd->info.mask |= CDC_CD_R;
		if ((buffer[11] & 2) == 0)
			cd->info.mask |= CDC_CD_RW;
		if ((buffer[12] & 1) == 0)
			cd->info.mask |= CDC_PLAY_AUDIO;
		if ((buffer[14] & 1) == 0)
			cd->info.mask |= CDC_LOCK;
		if ((buffer[14] & 8) == 0)
			cd->info.mask |= CDC_OPEN_TRAY;
		if ((buffer[14] >> 6) == 0)
			cd->info.mask |= CDC_CLOSE_TRAY;
	}
}
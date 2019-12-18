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
struct osd_state {int dummy; } ;
typedef  enum osd_rom_clut { ____Placeholder_osd_rom_clut } osd_rom_clut ;

/* Variables and functions */
 int /*<<< orphan*/  OSD_MISCCTL ; 
 int /*<<< orphan*/  OSD_MISCCTL_RSEL ; 
 int ROM_CLUT0 ; 
 int /*<<< orphan*/  osd_clear (struct osd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osd_set (struct osd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _osd_set_rom_clut(struct osd_state *sd,
			      enum osd_rom_clut rom_clut)
{
	if (rom_clut == ROM_CLUT0)
		osd_clear(sd, OSD_MISCCTL_RSEL, OSD_MISCCTL);
	else
		osd_set(sd, OSD_MISCCTL_RSEL, OSD_MISCCTL);
}
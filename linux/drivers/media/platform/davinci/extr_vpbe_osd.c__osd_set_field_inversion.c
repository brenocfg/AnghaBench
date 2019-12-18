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

/* Variables and functions */
 int /*<<< orphan*/  OSD_MODE ; 
 unsigned int OSD_MODE_FSINV ; 
 int /*<<< orphan*/  osd_modify (struct osd_state*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _osd_set_field_inversion(struct osd_state *sd, int enable)
{
	unsigned fsinv = 0;

	if (enable)
		fsinv = OSD_MODE_FSINV;

	osd_modify(sd, OSD_MODE_FSINV, fsinv, OSD_MODE);
}
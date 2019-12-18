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
struct osd_state {scalar_t__ vpbe_type; int /*<<< orphan*/  rom_clut; int /*<<< orphan*/  field_inversion; int /*<<< orphan*/  yc_pixfmt; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PIXFMT_YCBCRI ; 
 int /*<<< orphan*/  ROM_CLUT1 ; 
 scalar_t__ VPBE_VERSION_3 ; 
 int /*<<< orphan*/  WIN_OSD0 ; 
 int /*<<< orphan*/  WIN_OSD1 ; 
 int /*<<< orphan*/  WIN_VID0 ; 
 int /*<<< orphan*/  WIN_VID1 ; 
 int /*<<< orphan*/  _osd_init (struct osd_state*) ; 
 int /*<<< orphan*/  _osd_set_field_inversion (struct osd_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _osd_set_rom_clut (struct osd_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osd_init_layer (struct osd_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int osd_initialize(struct osd_state *osd)
{
	if (osd == NULL)
		return -ENODEV;
	_osd_init(osd);

	/* set default Cb/Cr order */
	osd->yc_pixfmt = PIXFMT_YCBCRI;

	if (osd->vpbe_type == VPBE_VERSION_3) {
		/*
		 * ROM CLUT1 on the DM355 is similar (identical?) to ROM CLUT0
		 * on the DM6446, so make ROM_CLUT1 the default on the DM355.
		 */
		osd->rom_clut = ROM_CLUT1;
	}

	_osd_set_field_inversion(osd, osd->field_inversion);
	_osd_set_rom_clut(osd, osd->rom_clut);

	osd_init_layer(osd, WIN_OSD0);
	osd_init_layer(osd, WIN_VID0);
	osd_init_layer(osd, WIN_OSD1);
	osd_init_layer(osd, WIN_VID1);

	return 0;
}
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
struct ssb_sprom {int revision; int /*<<< orphan*/  leddc_off_time; int /*<<< orphan*/  leddc_on_time; int /*<<< orphan*/  alpha2; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm47xx_fill_board_data (struct ssb_sprom*,char const*,int) ; 
 int /*<<< orphan*/  bcm47xx_fill_sprom_ethernet (struct ssb_sprom*,char const*,int) ; 
 int /*<<< orphan*/  bcm47xx_fill_sprom_path_r45 (struct ssb_sprom*,char const*,int) ; 
 int /*<<< orphan*/  bcm47xx_fill_sprom_path_r4589 (struct ssb_sprom*,char const*,int) ; 
 int /*<<< orphan*/  bcm47xx_sprom_fill_auto (struct ssb_sprom*,char const*,int) ; 
 int /*<<< orphan*/  nvram_read_alpha2 (char const*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvram_read_leddc (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nvram_read_u8 (char const*,int /*<<< orphan*/ *,char*,int*,int /*<<< orphan*/ ,int) ; 

void bcm47xx_fill_sprom(struct ssb_sprom *sprom, const char *prefix,
			bool fallback)
{
	bcm47xx_fill_sprom_ethernet(sprom, prefix, fallback);
	bcm47xx_fill_board_data(sprom, prefix, fallback);

	nvram_read_u8(prefix, NULL, "sromrev", &sprom->revision, 0, fallback);

	/* Entries requiring custom functions */
	nvram_read_alpha2(prefix, "ccode", sprom->alpha2, fallback);
	if (sprom->revision >= 3)
		nvram_read_leddc(prefix, "leddc", &sprom->leddc_on_time,
				 &sprom->leddc_off_time, fallback);

	switch (sprom->revision) {
	case 4:
	case 5:
		bcm47xx_fill_sprom_path_r4589(sprom, prefix, fallback);
		bcm47xx_fill_sprom_path_r45(sprom, prefix, fallback);
		break;
	case 8:
	case 9:
		bcm47xx_fill_sprom_path_r4589(sprom, prefix, fallback);
		break;
	}

	bcm47xx_sprom_fill_auto(sprom, prefix, fallback);
}
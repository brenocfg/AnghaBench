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
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;
struct bttv {TYPE_1__ c; int /*<<< orphan*/  tuner_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  TUNER_ALPS_TSBB5_PAL_I ; 
 int /*<<< orphan*/  TUNER_PHILIPS_NTSC ; 
 int /*<<< orphan*/  TUNER_TEMIC_4066FY5_PAL_I ; 
 int /*<<< orphan*/ * eeprom_data ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void modtec_eeprom(struct bttv *btv)
{
	if( strncmp(&(eeprom_data[0x1e]),"Temic 4066 FY5",14) ==0) {
		btv->tuner_type=TUNER_TEMIC_4066FY5_PAL_I;
		pr_info("%d: Modtec: Tuner autodetected by eeprom: %s\n",
			btv->c.nr, &eeprom_data[0x1e]);
	} else if (strncmp(&(eeprom_data[0x1e]),"Alps TSBB5",10) ==0) {
		btv->tuner_type=TUNER_ALPS_TSBB5_PAL_I;
		pr_info("%d: Modtec: Tuner autodetected by eeprom: %s\n",
			btv->c.nr, &eeprom_data[0x1e]);
	} else if (strncmp(&(eeprom_data[0x1e]),"Philips FM1246",14) ==0) {
		btv->tuner_type=TUNER_PHILIPS_NTSC;
		pr_info("%d: Modtec: Tuner autodetected by eeprom: %s\n",
			btv->c.nr, &eeprom_data[0x1e]);
	} else {
		pr_info("%d: Modtec: Unknown TunerString: %s\n",
			btv->c.nr, &eeprom_data[0x1e]);
	}
}
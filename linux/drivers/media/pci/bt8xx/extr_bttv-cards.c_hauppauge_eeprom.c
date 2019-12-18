#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tveeprom {int model; int /*<<< orphan*/  has_radio; int /*<<< orphan*/  tuner_type; } ;
struct TYPE_3__ {size_t type; int /*<<< orphan*/  nr; } ;
struct bttv {int radio_uses_msp_demodulator; TYPE_1__ c; int /*<<< orphan*/  has_radio; int /*<<< orphan*/  tuner_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t BTTV_BOARD_HAUPPAUGE_IMPACTVCB ; 
 TYPE_2__* bttv_tvcards ; 
 int /*<<< orphan*/  eeprom_data ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  tveeprom_hauppauge_analog (struct tveeprom*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hauppauge_eeprom(struct bttv *btv)
{
	struct tveeprom tv;

	tveeprom_hauppauge_analog(&tv, eeprom_data);
	btv->tuner_type = tv.tuner_type;
	btv->has_radio  = tv.has_radio;

	pr_info("%d: Hauppauge eeprom indicates model#%d\n",
		btv->c.nr, tv.model);

	/*
	 * Some of the 878 boards have duplicate PCI IDs. Switch the board
	 * type based on model #.
	 */
	if(tv.model == 64900) {
		pr_info("%d: Switching board type from %s to %s\n",
			btv->c.nr,
			bttv_tvcards[btv->c.type].name,
			bttv_tvcards[BTTV_BOARD_HAUPPAUGE_IMPACTVCB].name);
		btv->c.type = BTTV_BOARD_HAUPPAUGE_IMPACTVCB;
	}

	/* The 61334 needs the msp3410 to do the radio demod to get sound */
	if (tv.model == 61334)
		btv->radio_uses_msp_demodulator = 1;
}
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
struct psmouse {struct elantech_data* private; } ;
struct TYPE_2__ {int hw_version; int /*<<< orphan*/  set_hw_resolution; } ;
struct elantech_data {int reg_10; int reg_11; int reg_21; int reg_07; TYPE_1__ info; } ;

/* Variables and functions */
 unsigned char ETP_R10_ABSOLUTE_MODE ; 
 int /*<<< orphan*/  ETP_READ_BACK_DELAY ; 
 int ETP_READ_BACK_TRIES ; 
 int /*<<< orphan*/  elantech_debug (char*,int) ; 
 int elantech_read_reg (struct psmouse*,int,unsigned char*) ; 
 int /*<<< orphan*/  elantech_write_reg (struct psmouse*,int,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_err (struct psmouse*,char*) ; 

__attribute__((used)) static int elantech_set_absolute_mode(struct psmouse *psmouse)
{
	struct elantech_data *etd = psmouse->private;
	unsigned char val;
	int tries = ETP_READ_BACK_TRIES;
	int rc = 0;

	switch (etd->info.hw_version) {
	case 1:
		etd->reg_10 = 0x16;
		etd->reg_11 = 0x8f;
		if (elantech_write_reg(psmouse, 0x10, etd->reg_10) ||
		    elantech_write_reg(psmouse, 0x11, etd->reg_11)) {
			rc = -1;
		}
		break;

	case 2:
					/* Windows driver values */
		etd->reg_10 = 0x54;
		etd->reg_11 = 0x88;	/* 0x8a */
		etd->reg_21 = 0x60;	/* 0x00 */
		if (elantech_write_reg(psmouse, 0x10, etd->reg_10) ||
		    elantech_write_reg(psmouse, 0x11, etd->reg_11) ||
		    elantech_write_reg(psmouse, 0x21, etd->reg_21)) {
			rc = -1;
		}
		break;

	case 3:
		if (etd->info.set_hw_resolution)
			etd->reg_10 = 0x0b;
		else
			etd->reg_10 = 0x01;

		if (elantech_write_reg(psmouse, 0x10, etd->reg_10))
			rc = -1;

		break;

	case 4:
		etd->reg_07 = 0x01;
		if (elantech_write_reg(psmouse, 0x07, etd->reg_07))
			rc = -1;

		goto skip_readback_reg_10; /* v4 has no reg 0x10 to read */
	}

	if (rc == 0) {
		/*
		 * Read back reg 0x10. For hardware version 1 we must make
		 * sure the absolute mode bit is set. For hardware version 2
		 * the touchpad is probably initializing and not ready until
		 * we read back the value we just wrote.
		 */
		do {
			rc = elantech_read_reg(psmouse, 0x10, &val);
			if (rc == 0)
				break;
			tries--;
			elantech_debug("retrying read (%d).\n", tries);
			msleep(ETP_READ_BACK_DELAY);
		} while (tries > 0);

		if (rc) {
			psmouse_err(psmouse,
				    "failed to read back register 0x10.\n");
		} else if (etd->info.hw_version == 1 &&
			   !(val & ETP_R10_ABSOLUTE_MODE)) {
			psmouse_err(psmouse,
				    "touchpad refuses to switch to absolute mode.\n");
			rc = -1;
		}
	}

 skip_readback_reg_10:
	if (rc)
		psmouse_err(psmouse, "failed to initialise registers.\n");

	return rc;
}
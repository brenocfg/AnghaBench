#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {int step_size; int strength; } ;
struct TYPE_6__ {TYPE_2__ eccreq; } ;
struct TYPE_4__ {int* data; } ;
struct nand_chip {TYPE_3__ base; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 

__attribute__((used)) static void hynix_nand_extract_ecc_requirements(struct nand_chip *chip,
						bool valid_jedecid)
{
	u8 ecc_level = (chip->id.data[4] >> 4) & 0x7;

	if (valid_jedecid) {
		/* Reference: H27UCG8T2E datasheet */
		chip->base.eccreq.step_size = 1024;

		switch (ecc_level) {
		case 0:
			chip->base.eccreq.step_size = 0;
			chip->base.eccreq.strength = 0;
			break;
		case 1:
			chip->base.eccreq.strength = 4;
			break;
		case 2:
			chip->base.eccreq.strength = 24;
			break;
		case 3:
			chip->base.eccreq.strength = 32;
			break;
		case 4:
			chip->base.eccreq.strength = 40;
			break;
		case 5:
			chip->base.eccreq.strength = 50;
			break;
		case 6:
			chip->base.eccreq.strength = 60;
			break;
		default:
			/*
			 * We should never reach this case, but if that
			 * happens, this probably means Hynix decided to use
			 * a different extended ID format, and we should find
			 * a way to support it.
			 */
			WARN(1, "Invalid ECC requirements");
		}
	} else {
		/*
		 * The ECC requirements field meaning depends on the
		 * NAND technology.
		 */
		u8 nand_tech = chip->id.data[5] & 0x7;

		if (nand_tech < 3) {
			/* > 26nm, reference: H27UBG8T2A datasheet */
			if (ecc_level < 5) {
				chip->base.eccreq.step_size = 512;
				chip->base.eccreq.strength = 1 << ecc_level;
			} else if (ecc_level < 7) {
				if (ecc_level == 5)
					chip->base.eccreq.step_size = 2048;
				else
					chip->base.eccreq.step_size = 1024;
				chip->base.eccreq.strength = 24;
			} else {
				/*
				 * We should never reach this case, but if that
				 * happens, this probably means Hynix decided
				 * to use a different extended ID format, and
				 * we should find a way to support it.
				 */
				WARN(1, "Invalid ECC requirements");
			}
		} else {
			/* <= 26nm, reference: H27UBG8T2B datasheet */
			if (!ecc_level) {
				chip->base.eccreq.step_size = 0;
				chip->base.eccreq.strength = 0;
			} else if (ecc_level < 5) {
				chip->base.eccreq.step_size = 512;
				chip->base.eccreq.strength = 1 << (ecc_level - 1);
			} else {
				chip->base.eccreq.step_size = 1024;
				chip->base.eccreq.strength = 24 +
							(8 * (ecc_level - 5));
			}
		}
	}
}
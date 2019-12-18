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
typedef  int /*<<< orphan*/  u8 ;
struct tveeprom {int model; } ;
struct saa7134_dev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tveeprom_hauppauge_analog (struct tveeprom*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hauppauge_eeprom(struct saa7134_dev *dev, u8 *eeprom_data)
{
	struct tveeprom tv;

	tveeprom_hauppauge_analog(&tv, eeprom_data);

	/* Make sure we support the board model */
	switch (tv.model) {
	case 67019: /* WinTV-HVR1110 (Retail, IR Blaster, hybrid, FM, SVid/Comp, 3.5mm audio in) */
	case 67109: /* WinTV-HVR1000 (Retail, IR Receive, analog, no FM, SVid/Comp, 3.5mm audio in) */
	case 67201: /* WinTV-HVR1150 (Retail, IR Receive, hybrid, FM, SVid/Comp, 3.5mm audio in) */
	case 67301: /* WinTV-HVR1000 (Retail, IR Receive, analog, no FM, SVid/Comp, 3.5mm audio in) */
	case 67209: /* WinTV-HVR1110 (Retail, IR Receive, hybrid, FM, SVid/Comp, 3.5mm audio in) */
	case 67559: /* WinTV-HVR1110 (OEM, no IR, hybrid, FM, SVid/Comp, RCA aud) */
	case 67569: /* WinTV-HVR1110 (OEM, no IR, hybrid, FM) */
	case 67579: /* WinTV-HVR1110 (OEM, no IR, hybrid, no FM) */
	case 67589: /* WinTV-HVR1110 (OEM, no IR, hybrid, no FM, SVid/Comp, RCA aud) */
	case 67599: /* WinTV-HVR1110 (OEM, no IR, hybrid, no FM, SVid/Comp, RCA aud) */
	case 67651: /* WinTV-HVR1150 (OEM, no IR, hybrid, FM, SVid/Comp, RCA aud) */
	case 67659: /* WinTV-HVR1110 (OEM, no IR, hybrid, FM, SVid/Comp, RCA aud) */
		break;
	default:
		pr_warn("%s: warning: unknown hauppauge model #%d\n",
			dev->name, tv.model);
		break;
	}

	pr_info("%s: hauppauge eeprom: model=%d\n",
	       dev->name, tv.model);
}
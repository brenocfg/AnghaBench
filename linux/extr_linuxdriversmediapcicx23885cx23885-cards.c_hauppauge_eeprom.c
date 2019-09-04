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
struct cx23885_dev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tveeprom_hauppauge_analog (struct tveeprom*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hauppauge_eeprom(struct cx23885_dev *dev, u8 *eeprom_data)
{
	struct tveeprom tv;

	tveeprom_hauppauge_analog(&tv, eeprom_data);

	/* Make sure we support the board model */
	switch (tv.model) {
	case 22001:
		/* WinTV-HVR1270 (PCIe, Retail, half height)
		 * ATSC/QAM and basic analog, IR Blast */
	case 22009:
		/* WinTV-HVR1210 (PCIe, Retail, half height)
		 * DVB-T and basic analog, IR Blast */
	case 22011:
		/* WinTV-HVR1270 (PCIe, Retail, half height)
		 * ATSC/QAM and basic analog, IR Recv */
	case 22019:
		/* WinTV-HVR1210 (PCIe, Retail, half height)
		 * DVB-T and basic analog, IR Recv */
	case 22021:
		/* WinTV-HVR1275 (PCIe, Retail, half height)
		 * ATSC/QAM and basic analog, IR Recv */
	case 22029:
		/* WinTV-HVR1210 (PCIe, Retail, half height)
		 * DVB-T and basic analog, IR Recv */
	case 22101:
		/* WinTV-HVR1270 (PCIe, Retail, full height)
		 * ATSC/QAM and basic analog, IR Blast */
	case 22109:
		/* WinTV-HVR1210 (PCIe, Retail, full height)
		 * DVB-T and basic analog, IR Blast */
	case 22111:
		/* WinTV-HVR1270 (PCIe, Retail, full height)
		 * ATSC/QAM and basic analog, IR Recv */
	case 22119:
		/* WinTV-HVR1210 (PCIe, Retail, full height)
		 * DVB-T and basic analog, IR Recv */
	case 22121:
		/* WinTV-HVR1275 (PCIe, Retail, full height)
		 * ATSC/QAM and basic analog, IR Recv */
	case 22129:
		/* WinTV-HVR1210 (PCIe, Retail, full height)
		 * DVB-T and basic analog, IR Recv */
	case 71009:
		/* WinTV-HVR1200 (PCIe, Retail, full height)
		 * DVB-T and basic analog */
	case 71100:
		/* WinTV-ImpactVCB-e (PCIe, Retail, half height)
		 * Basic analog */
	case 71359:
		/* WinTV-HVR1200 (PCIe, OEM, half height)
		 * DVB-T and basic analog */
	case 71439:
		/* WinTV-HVR1200 (PCIe, OEM, half height)
		 * DVB-T and basic analog */
	case 71449:
		/* WinTV-HVR1200 (PCIe, OEM, full height)
		 * DVB-T and basic analog */
	case 71939:
		/* WinTV-HVR1200 (PCIe, OEM, half height)
		 * DVB-T and basic analog */
	case 71949:
		/* WinTV-HVR1200 (PCIe, OEM, full height)
		 * DVB-T and basic analog */
	case 71959:
		/* WinTV-HVR1200 (PCIe, OEM, full height)
		 * DVB-T and basic analog */
	case 71979:
		/* WinTV-HVR1200 (PCIe, OEM, half height)
		 * DVB-T and basic analog */
	case 71999:
		/* WinTV-HVR1200 (PCIe, OEM, full height)
		 * DVB-T and basic analog */
	case 76601:
		/* WinTV-HVR1800lp (PCIe, Retail, No IR, Dual
			channel ATSC and MPEG2 HW Encoder */
	case 77001:
		/* WinTV-HVR1500 (Express Card, OEM, No IR, ATSC
			and Basic analog */
	case 77011:
		/* WinTV-HVR1500 (Express Card, Retail, No IR, ATSC
			and Basic analog */
	case 77041:
		/* WinTV-HVR1500Q (Express Card, OEM, No IR, ATSC/QAM
			and Basic analog */
	case 77051:
		/* WinTV-HVR1500Q (Express Card, Retail, No IR, ATSC/QAM
			and Basic analog */
	case 78011:
		/* WinTV-HVR1800 (PCIe, Retail, 3.5mm in, IR, No FM,
			Dual channel ATSC and MPEG2 HW Encoder */
	case 78501:
		/* WinTV-HVR1800 (PCIe, OEM, RCA in, No IR, FM,
			Dual channel ATSC and MPEG2 HW Encoder */
	case 78521:
		/* WinTV-HVR1800 (PCIe, OEM, RCA in, No IR, FM,
			Dual channel ATSC and MPEG2 HW Encoder */
	case 78531:
		/* WinTV-HVR1800 (PCIe, OEM, RCA in, No IR, No FM,
			Dual channel ATSC and MPEG2 HW Encoder */
	case 78631:
		/* WinTV-HVR1800 (PCIe, OEM, No IR, No FM,
			Dual channel ATSC and MPEG2 HW Encoder */
	case 79001:
		/* WinTV-HVR1250 (PCIe, Retail, IR, full height,
			ATSC and Basic analog */
	case 79101:
		/* WinTV-HVR1250 (PCIe, Retail, IR, half height,
			ATSC and Basic analog */
	case 79501:
		/* WinTV-HVR1250 (PCIe, No IR, half height,
			ATSC [at least] and Basic analog) */
	case 79561:
		/* WinTV-HVR1250 (PCIe, OEM, No IR, half height,
			ATSC and Basic analog */
	case 79571:
		/* WinTV-HVR1250 (PCIe, OEM, No IR, full height,
		 ATSC and Basic analog */
	case 79671:
		/* WinTV-HVR1250 (PCIe, OEM, No IR, half height,
			ATSC and Basic analog */
	case 80019:
		/* WinTV-HVR1400 (Express Card, Retail, IR,
		 * DVB-T and Basic analog */
	case 81509:
		/* WinTV-HVR1700 (PCIe, OEM, No IR, half height)
		 * DVB-T and MPEG2 HW Encoder */
	case 81519:
		/* WinTV-HVR1700 (PCIe, OEM, No IR, full height)
		 * DVB-T and MPEG2 HW Encoder */
		break;
	case 85021:
		/* WinTV-HVR1850 (PCIe, Retail, 3.5mm in, IR, FM,
			Dual channel ATSC and MPEG2 HW Encoder */
		break;
	case 85721:
		/* WinTV-HVR1290 (PCIe, OEM, RCA in, IR,
			Dual channel ATSC and Basic analog */
	case 121019:
		/* WinTV-HVR4400 (PCIe, DVB-S2, DVB-C/T) */
		break;
	case 121029:
		/* WinTV-HVR5500 (PCIe, DVB-S2, DVB-C/T) */
		break;
	case 150329:
		/* WinTV-HVR5525 (PCIe, DVB-S/S2, DVB-T/T2/C) */
		break;
	case 161111:
		/* WinTV-HVR-1265 K4 (PCIe, Analog/ATSC/QAM-B) */
		break;
	case 166100: /* 888 version, hybrid */
	case 166200: /* 885 version, DVB only */
		/* WinTV-QuadHD (DVB) Tuner Pair 1 (PCIe, IR, half height,
		   DVB-T/T2/C, DVB-T/T2/C */
		break;
	case 166101: /* 888 version, hybrid */
	case 166201: /* 885 version, DVB only */
		/* WinTV-QuadHD (DVB) Tuner Pair 2 (PCIe, IR, half height,
		   DVB-T/T2/C, DVB-T/T2/C */
		break;
	case 165100: /* 888 version, hybrid */
	case 165200: /* 885 version, digital only */
		/* WinTV-QuadHD (ATSC) Tuner Pair 1 (PCIe, IR, half height,
		 * ATSC/QAM-B, ATSC/QAM-B */
		break;
	case 165101: /* 888 version, hybrid */
	case 165201: /* 885 version, digital only */
		/* WinTV-QuadHD (ATSC) Tuner Pair 2 (PCIe, IR, half height,
		 * ATSC/QAM-B, ATSC/QAM-B */
		break;
	default:
		pr_warn("%s: warning: unknown hauppauge model #%d\n",
			dev->name, tv.model);
		break;
	}

	pr_info("%s: hauppauge eeprom: model=%d\n",
		dev->name, tv.model);
}
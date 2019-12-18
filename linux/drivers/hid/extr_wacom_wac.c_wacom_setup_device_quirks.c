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
struct wacom_features {int type; int device_type; int x_max; int y_max; scalar_t__ pktlen; int x_fuzz; int y_fuzz; int /*<<< orphan*/  quirks; scalar_t__ touch_max; } ;
struct wacom_wac {TYPE_2__* pen_input; struct wacom_features features; } ;
struct wacom {TYPE_1__* hdev; struct wacom_wac wacom_wac; } ;
struct TYPE_4__ {int /*<<< orphan*/  evbit; int /*<<< orphan*/  mscbit; int /*<<< orphan*/  absbit; int /*<<< orphan*/  keybit; } ;
struct TYPE_3__ {scalar_t__ bus; int product; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DISTANCE ; 
 int /*<<< orphan*/  ABS_MISC ; 
 int /*<<< orphan*/  ABS_TILT_X ; 
 int /*<<< orphan*/  ABS_TILT_Y ; 
 int /*<<< orphan*/  ABS_WHEEL ; 
 int /*<<< orphan*/  ABS_Z ; 
 int BAMBOO_PAD ; 
 int BAMBOO_PEN ; 
 int BAMBOO_PT ; 
 int BAMBOO_TOUCH ; 
 int /*<<< orphan*/  BTN_TOOL_AIRBRUSH ; 
 int /*<<< orphan*/  BTN_TOOL_BRUSH ; 
 int /*<<< orphan*/  BTN_TOOL_PENCIL ; 
 scalar_t__ BUS_BLUETOOTH ; 
#define  CINTIQ 149 
#define  CINTIQ_COMPANION_2 148 
#define  CINTIQ_HYBRID 147 
#define  DTK 146 
#define  DTU 145 
#define  DTUS 144 
#define  DTUSX 143 
 int /*<<< orphan*/  EV_MSC ; 
 int GRAPHIRE_BT ; 
 int INTUOS3S ; 
 int INTUOS5S ; 
 int INTUOSHT ; 
 int INTUOSHT2 ; 
 int INTUOSHT3_BT ; 
 int INTUOSP2S_BT ; 
 int INTUOSP2_BT ; 
 int INTUOSPL ; 
 int /*<<< orphan*/  MSC_SERIAL ; 
#define  MTSCREEN 142 
#define  MTTPC 141 
#define  MTTPC_B 140 
#define  PL 139 
 int REMOTE ; 
#define  TABLETPC 138 
#define  TABLETPC2FG 137 
#define  TABLETPCE 136 
#define  WACOM_13HD 135 
#define  WACOM_21UX2 134 
#define  WACOM_22HD 133 
#define  WACOM_24HD 132 
#define  WACOM_24HDT 131 
#define  WACOM_27QHD 130 
#define  WACOM_27QHDT 129 
#define  WACOM_BEE 128 
 int WACOM_DEVICETYPE_DIRECT ; 
 int WACOM_DEVICETYPE_PAD ; 
 int WACOM_DEVICETYPE_PEN ; 
 int WACOM_DEVICETYPE_TOUCH ; 
 int WACOM_DEVICETYPE_WL_MONITOR ; 
 int WACOM_G4 ; 
 int WACOM_MO ; 
 scalar_t__ WACOM_PKGLEN_BBTOUCH ; 
 scalar_t__ WACOM_PKGLEN_BBTOUCH3 ; 
 int /*<<< orphan*/  WACOM_QUIRK_BATTERY ; 
 int /*<<< orphan*/  WACOM_QUIRK_BBTOUCH_LOWRES ; 
 int /*<<< orphan*/  WACOM_QUIRK_TOOLSERIAL ; 
 int WIRELESS ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void wacom_setup_device_quirks(struct wacom *wacom)
{
	struct wacom_wac *wacom_wac = &wacom->wacom_wac;
	struct wacom_features *features = &wacom->wacom_wac.features;

	/* The pen and pad share the same interface on most devices */
	if (features->type == GRAPHIRE_BT || features->type == WACOM_G4 ||
	    features->type == DTUS ||
	    (features->type >= INTUOS3S && features->type <= WACOM_MO)) {
		if (features->device_type & WACOM_DEVICETYPE_PEN)
			features->device_type |= WACOM_DEVICETYPE_PAD;
	}

	/* touch device found but size is not defined. use default */
	if (features->device_type & WACOM_DEVICETYPE_TOUCH && !features->x_max) {
		features->x_max = 1023;
		features->y_max = 1023;
	}

	/*
	 * Intuos5/Pro and Bamboo 3rd gen have no useful data about its
	 * touch interface in its HID descriptor. If this is the touch
	 * interface (PacketSize of WACOM_PKGLEN_BBTOUCH3), override the
	 * tablet values.
	 */
	if ((features->type >= INTUOS5S && features->type <= INTUOSPL) ||
		(features->type >= INTUOSHT && features->type <= BAMBOO_PT)) {
		if (features->pktlen == WACOM_PKGLEN_BBTOUCH3) {
			if (features->touch_max)
				features->device_type |= WACOM_DEVICETYPE_TOUCH;
			if (features->type >= INTUOSHT && features->type <= BAMBOO_PT)
				features->device_type |= WACOM_DEVICETYPE_PAD;

			if (features->type == INTUOSHT2) {
				features->x_max = features->x_max / 10;
				features->y_max = features->y_max / 10;
			}
			else {
				features->x_max = 4096;
				features->y_max = 4096;
			}
		}
		else if (features->pktlen == WACOM_PKGLEN_BBTOUCH) {
			features->device_type |= WACOM_DEVICETYPE_PAD;
		}
	}

	/*
	 * Hack for the Bamboo One:
	 * the device presents a PAD/Touch interface as most Bamboos and even
	 * sends ghosts PAD data on it. However, later, we must disable this
	 * ghost interface, and we can not detect it unless we set it here
	 * to WACOM_DEVICETYPE_PAD or WACOM_DEVICETYPE_TOUCH.
	 */
	if (features->type == BAMBOO_PEN &&
	    features->pktlen == WACOM_PKGLEN_BBTOUCH3)
		features->device_type |= WACOM_DEVICETYPE_PAD;

	/*
	 * Raw Wacom-mode pen and touch events both come from interface
	 * 0, whose HID descriptor has an application usage of 0xFF0D
	 * (i.e., WACOM_HID_WD_DIGITIZER). We route pen packets back
	 * out through the HID_GENERIC device created for interface 1,
	 * so rewrite this one to be of type WACOM_DEVICETYPE_TOUCH.
	 */
	if (features->type == BAMBOO_PAD)
		features->device_type = WACOM_DEVICETYPE_TOUCH;

	if (features->type == REMOTE)
		features->device_type = WACOM_DEVICETYPE_PAD;

	if (features->type == INTUOSP2_BT ||
	    features->type == INTUOSP2S_BT) {
		features->device_type |= WACOM_DEVICETYPE_PEN |
					 WACOM_DEVICETYPE_PAD |
					 WACOM_DEVICETYPE_TOUCH;
		features->quirks |= WACOM_QUIRK_BATTERY;
	}

	if (features->type == INTUOSHT3_BT) {
		features->device_type |= WACOM_DEVICETYPE_PEN |
					 WACOM_DEVICETYPE_PAD;
		features->quirks |= WACOM_QUIRK_BATTERY;
	}

	switch (features->type) {
	case PL:
	case DTU:
	case DTUS:
	case DTUSX:
	case WACOM_21UX2:
	case WACOM_22HD:
	case DTK:
	case WACOM_24HD:
	case WACOM_27QHD:
	case CINTIQ_HYBRID:
	case CINTIQ_COMPANION_2:
	case CINTIQ:
	case WACOM_BEE:
	case WACOM_13HD:
	case WACOM_24HDT:
	case WACOM_27QHDT:
	case TABLETPC:
	case TABLETPCE:
	case TABLETPC2FG:
	case MTSCREEN:
	case MTTPC:
	case MTTPC_B:
		features->device_type |= WACOM_DEVICETYPE_DIRECT;
		break;
	}

	if (wacom->hdev->bus == BUS_BLUETOOTH)
		features->quirks |= WACOM_QUIRK_BATTERY;

	/* quirk for bamboo touch with 2 low res touches */
	if ((features->type == BAMBOO_PT || features->type == BAMBOO_TOUCH) &&
	    features->pktlen == WACOM_PKGLEN_BBTOUCH) {
		features->x_max <<= 5;
		features->y_max <<= 5;
		features->x_fuzz <<= 5;
		features->y_fuzz <<= 5;
		features->quirks |= WACOM_QUIRK_BBTOUCH_LOWRES;
	}

	if (features->type == WIRELESS) {
		if (features->device_type == WACOM_DEVICETYPE_WL_MONITOR) {
			features->quirks |= WACOM_QUIRK_BATTERY;
		}
	}

	if (features->type == REMOTE)
		features->device_type |= WACOM_DEVICETYPE_WL_MONITOR;

	/* HID descriptor for DTK-2451 / DTH-2452 claims to report lots
	 * of things it shouldn't. Lets fix up the damage...
	 */
	if (wacom->hdev->product == 0x382 || wacom->hdev->product == 0x37d) {
		features->quirks &= ~WACOM_QUIRK_TOOLSERIAL;
		__clear_bit(BTN_TOOL_BRUSH, wacom_wac->pen_input->keybit);
		__clear_bit(BTN_TOOL_PENCIL, wacom_wac->pen_input->keybit);
		__clear_bit(BTN_TOOL_AIRBRUSH, wacom_wac->pen_input->keybit);
		__clear_bit(ABS_Z, wacom_wac->pen_input->absbit);
		__clear_bit(ABS_DISTANCE, wacom_wac->pen_input->absbit);
		__clear_bit(ABS_TILT_X, wacom_wac->pen_input->absbit);
		__clear_bit(ABS_TILT_Y, wacom_wac->pen_input->absbit);
		__clear_bit(ABS_WHEEL, wacom_wac->pen_input->absbit);
		__clear_bit(ABS_MISC, wacom_wac->pen_input->absbit);
		__clear_bit(MSC_SERIAL, wacom_wac->pen_input->mscbit);
		__clear_bit(EV_MSC, wacom_wac->pen_input->evbit);
	}
}
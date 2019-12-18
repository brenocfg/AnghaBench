#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tveeprom {int /*<<< orphan*/  audio_processor; scalar_t__ tuner_type; } ;
struct TYPE_5__ {scalar_t__ valid; int /*<<< orphan*/  tuner_gpio; int /*<<< orphan*/  name; } ;
struct em28xx {scalar_t__ em28xx_sensor; int model; int i2s_speed; int has_msp34xx; scalar_t__* amux_map; scalar_t__ tuner_type; int /*<<< orphan*/ * eedata; TYPE_2__* intf; TYPE_1__ board; scalar_t__ is_webcam; } ;
struct TYPE_8__ {scalar_t__ amux; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {scalar_t__ tuner_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  EM2750_BOARD_UNKNOWN 142 
#define  EM2800_BOARD_UNKNOWN 141 
#define  EM28174_BOARD_HAUPPAUGE_WINTV_DUALHD_01595 140 
#define  EM28174_BOARD_HAUPPAUGE_WINTV_DUALHD_DVB 139 
#define  EM2820_BOARD_HAUPPAUGE_WINTV_USB_2 138 
#define  EM2820_BOARD_KWORLD_PVRTV2800RF 137 
#define  EM2820_BOARD_UNKNOWN 136 
 int EM2820_R08_GPIO_CTRL ; 
#define  EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900 135 
#define  EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900_R2 134 
#define  EM2880_BOARD_MSI_DIGIVOX_AD 133 
#define  EM2882_BOARD_KWORLD_ATSC_315U 132 
#define  EM2882_BOARD_KWORLD_VS_DVBT 131 
#define  EM2883_BOARD_HAUPPAUGE_WINTV_HVR_850 130 
#define  EM2883_BOARD_HAUPPAUGE_WINTV_HVR_950 129 
#define  EM2884_BOARD_HAUPPAUGE_WINTV_HVR_930C 128 
 scalar_t__ EM28XX_AMUX_UNUSED ; 
 int /*<<< orphan*/  EM28XX_ANALOG_MODE ; 
 scalar_t__ EM28XX_BOARD_NOT_VALIDATED ; 
 scalar_t__ EM28XX_NOSENSOR ; 
 TYPE_4__* INPUT (int) ; 
 int MAX_EM28XX_INPUT ; 
 int /*<<< orphan*/  TVEEPROM_AUDPROC_MSP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* em28xx_boards ; 
 int /*<<< orphan*/  em28xx_detect_sensor (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_gpio_set (struct em28xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em28xx_hint_board (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_pre_card_setup (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_set_mode (struct em28xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em28xx_set_model (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_write_reg (struct em28xx*,int,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_module (char*) ; 
 scalar_t__ tuner ; 
 int /*<<< orphan*/  tveeprom_hauppauge_analog (struct tveeprom*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void em28xx_card_setup(struct em28xx *dev)
{
	int i, j, idx;
	bool duplicate_entry;

	/*
	 * If the device can be a webcam, seek for a sensor.
	 * If sensor is not found, then it isn't a webcam.
	 */
	if (dev->is_webcam) {
		em28xx_detect_sensor(dev);
		if (dev->em28xx_sensor == EM28XX_NOSENSOR)
			/* NOTE: error/unknown sensor/no sensor */
			dev->is_webcam = 0;
	}

	switch (dev->model) {
	case EM2750_BOARD_UNKNOWN:
	case EM2820_BOARD_UNKNOWN:
	case EM2800_BOARD_UNKNOWN:
		/*
		 * The K-WORLD DVB-T 310U is detected as an MSI Digivox AD.
		 *
		 * This occurs because they share identical USB vendor and
		 * product IDs.
		 *
		 * What we do here is look up the EEPROM hash of the K-WORLD
		 * and if it is found then we decide that we do not have
		 * a DIGIVOX and reset the device to the K-WORLD instead.
		 *
		 * This solution is only valid if they do not share eeprom
		 * hash identities which has not been determined as yet.
		 */
		if (em28xx_hint_board(dev) < 0) {
			dev_err(&dev->intf->dev, "Board not discovered\n");
		} else {
			em28xx_set_model(dev);
			em28xx_pre_card_setup(dev);
		}
		break;
	default:
		em28xx_set_model(dev);
	}

	dev_info(&dev->intf->dev, "Identified as %s (card=%d)\n",
		 dev->board.name, dev->model);

	dev->tuner_type = em28xx_boards[dev->model].tuner_type;

	/* request some modules */
	switch (dev->model) {
	case EM2820_BOARD_HAUPPAUGE_WINTV_USB_2:
	case EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900:
	case EM2880_BOARD_HAUPPAUGE_WINTV_HVR_900_R2:
	case EM2883_BOARD_HAUPPAUGE_WINTV_HVR_850:
	case EM2883_BOARD_HAUPPAUGE_WINTV_HVR_950:
	case EM2884_BOARD_HAUPPAUGE_WINTV_HVR_930C:
	case EM28174_BOARD_HAUPPAUGE_WINTV_DUALHD_DVB:
	case EM28174_BOARD_HAUPPAUGE_WINTV_DUALHD_01595:
	{
		struct tveeprom tv;

		if (!dev->eedata)
			break;
#if defined(CONFIG_MODULES) && defined(MODULE)
		request_module("tveeprom");
#endif
		/* Call first TVeeprom */

		tveeprom_hauppauge_analog(&tv, dev->eedata);

		dev->tuner_type = tv.tuner_type;

		if (tv.audio_processor == TVEEPROM_AUDPROC_MSP) {
			dev->i2s_speed = 2048000;
			dev->has_msp34xx = 1;
		}
		break;
	}
	case EM2882_BOARD_KWORLD_ATSC_315U:
		em28xx_write_reg(dev, 0x0d, 0x42);
		usleep_range(10000, 11000);
		em28xx_write_reg(dev, EM2820_R08_GPIO_CTRL, 0xfd);
		usleep_range(10000, 11000);
		break;
	case EM2820_BOARD_KWORLD_PVRTV2800RF:
		/* GPIO enables sound on KWORLD PVR TV 2800RF */
		em28xx_write_reg(dev, EM2820_R08_GPIO_CTRL, 0xf9);
		break;
	case EM2820_BOARD_UNKNOWN:
	case EM2800_BOARD_UNKNOWN:
		/*
		 * The K-WORLD DVB-T 310U is detected as an MSI Digivox AD.
		 *
		 * This occurs because they share identical USB vendor and
		 * product IDs.
		 *
		 * What we do here is look up the EEPROM hash of the K-WORLD
		 * and if it is found then we decide that we do not have
		 * a DIGIVOX and reset the device to the K-WORLD instead.
		 *
		 * This solution is only valid if they do not share eeprom
		 * hash identities which has not been determined as yet.
		 */
	case EM2880_BOARD_MSI_DIGIVOX_AD:
		if (!em28xx_hint_board(dev))
			em28xx_set_model(dev);

		/*
		 * In cases where we had to use a board hint, the call to
		 * em28xx_set_mode() in em28xx_pre_card_setup() was a no-op,
		 * so make the call now so the analog GPIOs are set properly
		 * before probing the i2c bus.
		 */
		em28xx_gpio_set(dev, dev->board.tuner_gpio);
		em28xx_set_mode(dev, EM28XX_ANALOG_MODE);
		break;

		/*
		 * The Dikom DK300 is detected as an Kworld VS-DVB-T 323UR.
		 *
		 * This occurs because they share identical USB vendor and
		 * product IDs.
		 *
		 * What we do here is look up the EEPROM hash of the Dikom
		 * and if it is found then we decide that we do not have
		 * a Kworld and reset the device to the Dikom instead.
		 *
		 * This solution is only valid if they do not share eeprom
		 * hash identities which has not been determined as yet.
		 */
	case EM2882_BOARD_KWORLD_VS_DVBT:
		if (!em28xx_hint_board(dev))
			em28xx_set_model(dev);

		/*
		 * In cases where we had to use a board hint, the call to
		 * em28xx_set_mode() in em28xx_pre_card_setup() was a no-op,
		 * so make the call now so the analog GPIOs are set properly
		 * before probing the i2c bus.
		 */
		em28xx_gpio_set(dev, dev->board.tuner_gpio);
		em28xx_set_mode(dev, EM28XX_ANALOG_MODE);
		break;
	}

	if (dev->board.valid == EM28XX_BOARD_NOT_VALIDATED) {
		dev_err(&dev->intf->dev,
			"\n\n"
			"The support for this board weren't valid yet.\n"
			"Please send a report of having this working\n"
			"not to V4L mailing list (and/or to other addresses)\n\n");
	}

	/* Free eeprom data memory */
	kfree(dev->eedata);
	dev->eedata = NULL;

	/* Allow override tuner type by a module parameter */
	if (tuner >= 0)
		dev->tuner_type = tuner;

	/*
	 * Dynamically generate a list of valid audio inputs for this
	 * specific board, mapping them via enum em28xx_amux.
	 */

	idx = 0;
	for (i = 0; i < MAX_EM28XX_INPUT; i++) {
		if (!INPUT(i)->type)
			continue;

		/* Skip already mapped audio inputs */
		duplicate_entry = false;
		for (j = 0; j < idx; j++) {
			if (INPUT(i)->amux == dev->amux_map[j]) {
				duplicate_entry = true;
				break;
			}
		}
		if (duplicate_entry)
			continue;

		dev->amux_map[idx++] = INPUT(i)->amux;
	}
	for (; idx < MAX_EM28XX_INPUT; idx++)
		dev->amux_map[idx] = EM28XX_AMUX_UNUSED;
}
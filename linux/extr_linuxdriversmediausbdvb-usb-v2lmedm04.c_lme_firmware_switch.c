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
struct TYPE_2__ {int /*<<< orphan*/  idProduct; } ;
struct usb_device {int /*<<< orphan*/  dev; TYPE_1__ descriptor; } ;
struct lme2510_state {int dvb_usb_lme2510_firmware; } ;
struct firmware {int dummy; } ;
struct dvb_usb_device {struct usb_device* udev; struct lme2510_state* priv; } ;

/* Variables and functions */
 void* TUNER_DEFAULT ; 
#define  TUNER_LG 130 
 int TUNER_RS2000 ; 
#define  TUNER_S0194 129 
#define  TUNER_S7395 128 
 int dvb_usb_lme2510_firmware ; 
 char* fw_c_lg ; 
 char* fw_c_rs2000 ; 
 char* fw_c_s0194 ; 
 char* fw_c_s7395 ; 
 char* fw_lg ; 
 char* fw_s0194 ; 
 int /*<<< orphan*/  info (char*,char const*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lme_coldreset (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *lme_firmware_switch(struct dvb_usb_device *d, int cold)
{
	struct lme2510_state *st = d->priv;
	struct usb_device *udev = d->udev;
	const struct firmware *fw = NULL;
	const char *fw_lme;
	int ret = 0;

	cold = (cold > 0) ? (cold & 1) : 0;

	switch (le16_to_cpu(udev->descriptor.idProduct)) {
	case 0x1122:
		switch (st->dvb_usb_lme2510_firmware) {
		default:
		case TUNER_S0194:
			fw_lme = fw_s0194;
			ret = request_firmware(&fw, fw_lme, &udev->dev);
			if (ret == 0) {
				st->dvb_usb_lme2510_firmware = TUNER_S0194;
				cold = 0;
				break;
			}
			/* fall through */
		case TUNER_LG:
			fw_lme = fw_lg;
			ret = request_firmware(&fw, fw_lme, &udev->dev);
			if (ret == 0) {
				st->dvb_usb_lme2510_firmware = TUNER_LG;
				break;
			}
			st->dvb_usb_lme2510_firmware = TUNER_DEFAULT;
			break;
		}
		break;
	case 0x1120:
		switch (st->dvb_usb_lme2510_firmware) {
		default:
		case TUNER_S7395:
			fw_lme = fw_c_s7395;
			ret = request_firmware(&fw, fw_lme, &udev->dev);
			if (ret == 0) {
				st->dvb_usb_lme2510_firmware = TUNER_S7395;
				cold = 0;
				break;
			}
			/* fall through */
		case TUNER_LG:
			fw_lme = fw_c_lg;
			ret = request_firmware(&fw, fw_lme, &udev->dev);
			if (ret == 0) {
				st->dvb_usb_lme2510_firmware = TUNER_LG;
				break;
			}
			/* fall through */
		case TUNER_S0194:
			fw_lme = fw_c_s0194;
			ret = request_firmware(&fw, fw_lme, &udev->dev);
			if (ret == 0) {
				st->dvb_usb_lme2510_firmware = TUNER_S0194;
				break;
			}
			st->dvb_usb_lme2510_firmware = TUNER_DEFAULT;
			cold = 0;
			break;
		}
		break;
	case 0x22f0:
		fw_lme = fw_c_rs2000;
		st->dvb_usb_lme2510_firmware = TUNER_RS2000;
		break;
	default:
		fw_lme = fw_c_s7395;
	}

	release_firmware(fw);

	if (cold) {
		dvb_usb_lme2510_firmware = st->dvb_usb_lme2510_firmware;
		info("FRM Changing to %s firmware", fw_lme);
		lme_coldreset(d);
		return NULL;
	}

	return fw_lme;
}
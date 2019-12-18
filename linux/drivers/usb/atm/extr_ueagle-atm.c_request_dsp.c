#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uea_softc {TYPE_2__* dsp_firm; TYPE_1__* usb_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ADI930 ; 
 char* DSP4I_FIRMWARE ; 
 char* DSP4P_FIRMWARE ; 
 char* DSP9I_FIRMWARE ; 
 char* DSP9P_FIRMWARE ; 
 char* DSPEI_FIRMWARE ; 
 char* DSPEP_FIRMWARE ; 
 scalar_t__ EAGLE_IV ; 
 int EILSEQ ; 
 int /*<<< orphan*/  INS_TO_USBDEV (struct uea_softc*) ; 
 scalar_t__ IS_ISDN (struct uea_softc*) ; 
 scalar_t__ UEA_CHIP_VERSION (struct uea_softc*) ; 
 int check_dsp_e1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int check_dsp_e4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (TYPE_2__*) ; 
 int request_firmware (TYPE_2__**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uea_err (int /*<<< orphan*/ ,char*,char*,...) ; 

__attribute__((used)) static int request_dsp(struct uea_softc *sc)
{
	int ret;
	char *dsp_name;

	if (UEA_CHIP_VERSION(sc) == EAGLE_IV) {
		if (IS_ISDN(sc))
			dsp_name = DSP4I_FIRMWARE;
		else
			dsp_name = DSP4P_FIRMWARE;
	} else if (UEA_CHIP_VERSION(sc) == ADI930) {
		if (IS_ISDN(sc))
			dsp_name = DSP9I_FIRMWARE;
		else
			dsp_name = DSP9P_FIRMWARE;
	} else {
		if (IS_ISDN(sc))
			dsp_name = DSPEI_FIRMWARE;
		else
			dsp_name = DSPEP_FIRMWARE;
	}

	ret = request_firmware(&sc->dsp_firm, dsp_name, &sc->usb_dev->dev);
	if (ret < 0) {
		uea_err(INS_TO_USBDEV(sc),
		       "requesting firmware %s failed with error %d\n",
			dsp_name, ret);
		return ret;
	}

	if (UEA_CHIP_VERSION(sc) == EAGLE_IV)
		ret = check_dsp_e4(sc->dsp_firm->data, sc->dsp_firm->size);
	else
		ret = check_dsp_e1(sc->dsp_firm->data, sc->dsp_firm->size);

	if (ret) {
		uea_err(INS_TO_USBDEV(sc), "firmware %s is corrupted\n",
		       dsp_name);
		release_firmware(sc->dsp_firm);
		sc->dsp_firm = NULL;
		return -EILSEQ;
	}

	return 0;
}
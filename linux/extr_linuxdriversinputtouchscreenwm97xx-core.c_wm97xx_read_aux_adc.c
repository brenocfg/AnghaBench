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
typedef  int u16 ;
struct wm97xx {scalar_t__ id; int pen_probably_down; int /*<<< orphan*/  codec_mutex; TYPE_1__* codec; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int (* poll_sample ) (struct wm97xx*,int,int*) ;int /*<<< orphan*/  (* dig_enable ) (struct wm97xx*,int) ;int /*<<< orphan*/  (* dig_restore ) (struct wm97xx*) ;int /*<<< orphan*/  (* aux_prepare ) (struct wm97xx*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_EXTENDED_MID ; 
 int EBUSY ; 
 int RC_VALID ; 
 scalar_t__ WM9713_ID2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct wm97xx*) ; 
 int stub2 (struct wm97xx*,int,int*) ; 
 int /*<<< orphan*/  stub3 (struct wm97xx*) ; 
 int /*<<< orphan*/  stub4 (struct wm97xx*,int) ; 
 int wm97xx_reg_read (struct wm97xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm97xx_reg_write (struct wm97xx*,int /*<<< orphan*/ ,int) ; 

int wm97xx_read_aux_adc(struct wm97xx *wm, u16 adcsel)
{
	int power_adc = 0, auxval;
	u16 power = 0;
	int rc = 0;
	int timeout = 0;

	/* get codec */
	mutex_lock(&wm->codec_mutex);

	/* When the touchscreen is not in use, we may have to power up
	 * the AUX ADC before we can use sample the AUX inputs->
	 */
	if (wm->id == WM9713_ID2 &&
	    (power = wm97xx_reg_read(wm, AC97_EXTENDED_MID)) & 0x8000) {
		power_adc = 1;
		wm97xx_reg_write(wm, AC97_EXTENDED_MID, power & 0x7fff);
	}

	/* Prepare the codec for AUX reading */
	wm->codec->aux_prepare(wm);

	/* Turn polling mode on to read AUX ADC */
	wm->pen_probably_down = 1;

	while (rc != RC_VALID && timeout++ < 5)
		rc = wm->codec->poll_sample(wm, adcsel, &auxval);

	if (power_adc)
		wm97xx_reg_write(wm, AC97_EXTENDED_MID, power | 0x8000);

	wm->codec->dig_restore(wm);

	wm->pen_probably_down = 0;

	if (timeout >= 5) {
		dev_err(wm->dev,
			"timeout reading auxadc %d, disabling digitiser\n",
			adcsel);
		wm->codec->dig_enable(wm, false);
	}

	mutex_unlock(&wm->codec_mutex);
	return (rc == RC_VALID ? auxval & 0xfff : -EBUSY);
}
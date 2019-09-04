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
typedef  int u16 ;
struct wm8350 {int /*<<< orphan*/  auxadc_mutex; int /*<<< orphan*/  dev; int /*<<< orphan*/  auxadc_done; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WM8350_AUX1_READBACK ; 
 int WM8350_AUXADC_AUX1 ; 
 int WM8350_AUXADC_DATA1_MASK ; 
 int WM8350_AUXADC_ENA ; 
 int WM8350_AUXADC_POLL ; 
 int WM8350_AUXADC_TEMP ; 
 int WM8350_AUXADC_USB ; 
 scalar_t__ WM8350_DIGITISER_CONTROL_1 ; 
 scalar_t__ WM8350_POWER_MGMT_5 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wm8350_reg_read (struct wm8350*,scalar_t__) ; 
 int /*<<< orphan*/  wm8350_reg_write (struct wm8350*,scalar_t__,int) ; 

int wm8350_read_auxadc(struct wm8350 *wm8350, int channel, int scale, int vref)
{
	u16 reg, result = 0;

	if (channel < WM8350_AUXADC_AUX1 || channel > WM8350_AUXADC_TEMP)
		return -EINVAL;
	if (channel >= WM8350_AUXADC_USB && channel <= WM8350_AUXADC_TEMP
	    && (scale != 0 || vref != 0))
		return -EINVAL;

	mutex_lock(&wm8350->auxadc_mutex);

	/* Turn on the ADC */
	reg = wm8350_reg_read(wm8350, WM8350_POWER_MGMT_5);
	wm8350_reg_write(wm8350, WM8350_POWER_MGMT_5, reg | WM8350_AUXADC_ENA);

	if (scale || vref) {
		reg = scale << 13;
		reg |= vref << 12;
		wm8350_reg_write(wm8350, WM8350_AUX1_READBACK + channel, reg);
	}

	reg = wm8350_reg_read(wm8350, WM8350_DIGITISER_CONTROL_1);
	reg |= 1 << channel | WM8350_AUXADC_POLL;
	wm8350_reg_write(wm8350, WM8350_DIGITISER_CONTROL_1, reg);

	/* If a late IRQ left the completion signalled then consume
	 * the completion. */
	try_wait_for_completion(&wm8350->auxadc_done);

	/* We ignore the result of the completion and just check for a
	 * conversion result, allowing us to soldier on if the IRQ
	 * infrastructure is not set up for the chip. */
	wait_for_completion_timeout(&wm8350->auxadc_done, msecs_to_jiffies(5));

	reg = wm8350_reg_read(wm8350, WM8350_DIGITISER_CONTROL_1);
	if (reg & WM8350_AUXADC_POLL)
		dev_err(wm8350->dev, "adc chn %d read timeout\n", channel);
	else
		result = wm8350_reg_read(wm8350,
					 WM8350_AUX1_READBACK + channel);

	/* Turn off the ADC */
	reg = wm8350_reg_read(wm8350, WM8350_POWER_MGMT_5);
	wm8350_reg_write(wm8350, WM8350_POWER_MGMT_5,
			 reg & ~WM8350_AUXADC_ENA);

	mutex_unlock(&wm8350->auxadc_mutex);

	return result & WM8350_AUXADC_DATA1_MASK;
}
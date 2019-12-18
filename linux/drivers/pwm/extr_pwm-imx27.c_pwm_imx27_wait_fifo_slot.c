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
typedef  int /*<<< orphan*/  u32 ;
struct pwm_imx27_chip {scalar_t__ mmio_base; } ;
struct pwm_device {int dummy; } ;
struct pwm_chip {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MX3_PWMSR ; 
 int /*<<< orphan*/  MX3_PWMSR_FIFOAV ; 
 int MX3_PWMSR_FIFOAV_4WORDS ; 
 int /*<<< orphan*/  NSEC_PER_MSEC ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  msleep (unsigned int) ; 
 int /*<<< orphan*/  pwm_get_period (struct pwm_device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct pwm_imx27_chip* to_pwm_imx27_chip (struct pwm_chip*) ; 

__attribute__((used)) static void pwm_imx27_wait_fifo_slot(struct pwm_chip *chip,
				     struct pwm_device *pwm)
{
	struct pwm_imx27_chip *imx = to_pwm_imx27_chip(chip);
	struct device *dev = chip->dev;
	unsigned int period_ms;
	int fifoav;
	u32 sr;

	sr = readl(imx->mmio_base + MX3_PWMSR);
	fifoav = FIELD_GET(MX3_PWMSR_FIFOAV, sr);
	if (fifoav == MX3_PWMSR_FIFOAV_4WORDS) {
		period_ms = DIV_ROUND_UP(pwm_get_period(pwm),
					 NSEC_PER_MSEC);
		msleep(period_ms);

		sr = readl(imx->mmio_base + MX3_PWMSR);
		if (fifoav == FIELD_GET(MX3_PWMSR_FIFOAV, sr))
			dev_warn(dev, "there is no free FIFO slot\n");
	}
}
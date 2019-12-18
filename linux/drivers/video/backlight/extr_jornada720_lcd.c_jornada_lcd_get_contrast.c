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
struct lcd_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ FB_BLANK_UNBLANK ; 
 int GETCONTRAST ; 
 int TXDUMMY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ jornada_lcd_get_power (struct lcd_device*) ; 
 int jornada_ssp_byte (int) ; 
 int /*<<< orphan*/  jornada_ssp_end () ; 
 int /*<<< orphan*/  jornada_ssp_start () ; 

__attribute__((used)) static int jornada_lcd_get_contrast(struct lcd_device *ld)
{
	int ret;

	if (jornada_lcd_get_power(ld) != FB_BLANK_UNBLANK)
		return 0;

	jornada_ssp_start();

	if (jornada_ssp_byte(GETCONTRAST) == TXDUMMY) {
		ret = jornada_ssp_byte(TXDUMMY);
		goto success;
	}

	dev_err(&ld->dev, "failed to set contrast\n");
	ret = -ETIMEDOUT;

success:
	jornada_ssp_end();
	return ret;
}
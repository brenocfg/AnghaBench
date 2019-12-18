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
struct backlight_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BL_MAX_BRIGHT ; 
 int ETIMEDOUT ; 
 int GETBRIGHTNESS ; 
 int PPC_LDD1 ; 
 int PPSR ; 
 int TXDUMMY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int jornada_ssp_byte (int) ; 
 int /*<<< orphan*/  jornada_ssp_end () ; 
 int /*<<< orphan*/  jornada_ssp_start () ; 

__attribute__((used)) static int jornada_bl_get_brightness(struct backlight_device *bd)
{
	int ret;

	/* check if backlight is on */
	if (!(PPSR & PPC_LDD1))
		return 0;

	jornada_ssp_start();

	/* cmd should return txdummy */
	ret = jornada_ssp_byte(GETBRIGHTNESS);

	if (jornada_ssp_byte(GETBRIGHTNESS) != TXDUMMY) {
		dev_err(&bd->dev, "get brightness timeout\n");
		jornada_ssp_end();
		return -ETIMEDOUT;
	}

	/* exchange txdummy for value */
	ret = jornada_ssp_byte(TXDUMMY);

	jornada_ssp_end();

	return BL_MAX_BRIGHT - ret;
}
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
struct anx78xx_platform_data {scalar_t__ dvdd10; int /*<<< orphan*/  gpiod_pd; int /*<<< orphan*/  gpiod_reset; } ;
struct anx78xx {int powered; struct anx78xx_platform_data pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int regulator_disable (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void anx78xx_poweroff(struct anx78xx *anx78xx)
{
	struct anx78xx_platform_data *pdata = &anx78xx->pdata;
	int err;

	if (WARN_ON(!anx78xx->powered))
		return;

	gpiod_set_value_cansleep(pdata->gpiod_reset, 1);
	usleep_range(1000, 2000);

	gpiod_set_value_cansleep(pdata->gpiod_pd, 1);
	usleep_range(1000, 2000);

	if (pdata->dvdd10) {
		err = regulator_disable(pdata->dvdd10);
		if (err) {
			DRM_ERROR("Failed to disable DVDD10 regulator: %d\n",
				  err);
			return;
		}

		usleep_range(1000, 2000);
	}

	anx78xx->powered = false;
}
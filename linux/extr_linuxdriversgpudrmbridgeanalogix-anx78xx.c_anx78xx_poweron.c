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
struct anx78xx_platform_data {int /*<<< orphan*/  gpiod_reset; int /*<<< orphan*/  gpiod_pd; scalar_t__ dvdd10; } ;
struct anx78xx {int powered; int /*<<< orphan*/ * map; struct anx78xx_platform_data pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 size_t I2C_IDX_TX_P2 ; 
 int SP_AUDIO_PD ; 
 int SP_HDCP_PD ; 
 int SP_LINK_PD ; 
 int /*<<< orphan*/  SP_POWERDOWN_CTRL_REG ; 
 int SP_REGISTER_PD ; 
 int SP_TOTAL_PD ; 
 int SP_VIDEO_PD ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  anx78xx_clear_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  anx78xx_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int regulator_enable (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void anx78xx_poweron(struct anx78xx *anx78xx)
{
	struct anx78xx_platform_data *pdata = &anx78xx->pdata;
	int err;

	if (WARN_ON(anx78xx->powered))
		return;

	if (pdata->dvdd10) {
		err = regulator_enable(pdata->dvdd10);
		if (err) {
			DRM_ERROR("Failed to enable DVDD10 regulator: %d\n",
				  err);
			return;
		}

		usleep_range(1000, 2000);
	}

	gpiod_set_value_cansleep(pdata->gpiod_reset, 1);
	usleep_range(1000, 2000);

	gpiod_set_value_cansleep(pdata->gpiod_pd, 0);
	usleep_range(1000, 2000);

	gpiod_set_value_cansleep(pdata->gpiod_reset, 0);

	/* Power on registers module */
	anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P2], SP_POWERDOWN_CTRL_REG,
			 SP_HDCP_PD | SP_AUDIO_PD | SP_VIDEO_PD | SP_LINK_PD);
	anx78xx_clear_bits(anx78xx->map[I2C_IDX_TX_P2], SP_POWERDOWN_CTRL_REG,
			   SP_REGISTER_PD | SP_TOTAL_PD);

	anx78xx->powered = true;
}
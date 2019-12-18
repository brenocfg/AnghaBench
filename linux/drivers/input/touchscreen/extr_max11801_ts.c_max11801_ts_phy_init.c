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
struct max11801_data {struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APERTURE_CONF_REG ; 
 int /*<<< orphan*/  AUTO_MODE_TIME_CONF_REG ; 
 int /*<<< orphan*/  MESURE_AVER_CONF_REG ; 
 int /*<<< orphan*/  OP_MODE_CONF_REG ; 
 int /*<<< orphan*/  PANEL_SETUPTIME_CONF_REG ; 
 int /*<<< orphan*/  TOUCH_DETECT_PULLUP_CONF_REG ; 
 int /*<<< orphan*/  max11801_write_reg (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void max11801_ts_phy_init(struct max11801_data *data)
{
	struct i2c_client *client = data->client;

	/* Average X,Y, take 16 samples, average eight media sample */
	max11801_write_reg(client, MESURE_AVER_CONF_REG, 0xff);
	/* X,Y panel setup time set to 20us */
	max11801_write_reg(client, PANEL_SETUPTIME_CONF_REG, 0x11);
	/* Rough pullup time (2uS), Fine pullup time (10us)  */
	max11801_write_reg(client, TOUCH_DETECT_PULLUP_CONF_REG, 0x10);
	/* Auto mode init period = 5ms , scan period = 5ms*/
	max11801_write_reg(client, AUTO_MODE_TIME_CONF_REG, 0xaa);
	/* Aperture X,Y set to +- 4LSB */
	max11801_write_reg(client, APERTURE_CONF_REG, 0x33);
	/* Enable Power, enable Automode, enable Aperture, enable Average X,Y */
	max11801_write_reg(client, OP_MODE_CONF_REG, 0x36);
}
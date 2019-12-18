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
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM355EVM_MSP_FIRMREV ; 
 int /*<<< orphan*/  DM355EVM_MSP_LED ; 
 int /*<<< orphan*/  DM355EVM_MSP_VIDEO_IN ; 
 int EBUSY ; 
 int MSP_VIDEO_IMAGER ; 
 int add_children (struct i2c_client*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,char const*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,char const*) ; 
 int dm355evm_msp_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm355evm_msp_remove (struct i2c_client*) ; 
 int dm355evm_msp_write (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm355evm_power_off ; 
 struct i2c_client* msp430 ; 
 scalar_t__ msp_has_tvp () ; 
 int msp_led_cache ; 
 int /*<<< orphan*/  pm_power_off ; 

__attribute__((used)) static int
dm355evm_msp_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int		status;
	const char	*video = msp_has_tvp() ? "TVP5146" : "imager";

	if (msp430)
		return -EBUSY;
	msp430 = client;

	/* display revision status; doubles as sanity check */
	status = dm355evm_msp_read(DM355EVM_MSP_FIRMREV);
	if (status < 0)
		goto fail;
	dev_info(&client->dev, "firmware v.%02X, %s as video-in\n",
			status, video);

	/* mux video input:  either tvp5146 or some external imager */
	status = dm355evm_msp_write(msp_has_tvp() ? 0 : MSP_VIDEO_IMAGER,
			DM355EVM_MSP_VIDEO_IN);
	if (status < 0)
		dev_warn(&client->dev, "error %d muxing %s as video-in\n",
			status, video);

	/* init LED cache, and turn off the LEDs */
	msp_led_cache = 0xff;
	dm355evm_msp_write(msp_led_cache, DM355EVM_MSP_LED);

	/* export capabilities we support */
	status = add_children(client);
	if (status < 0)
		goto fail;

	/* PM hookup */
	pm_power_off = dm355evm_power_off;

	return 0;

fail:
	/* FIXME remove children ... */
	dm355evm_msp_remove(client);
	return status;
}
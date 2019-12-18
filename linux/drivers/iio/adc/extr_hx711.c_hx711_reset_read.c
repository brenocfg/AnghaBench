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
struct hx711_data {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int hx711_read (struct hx711_data*) ; 
 scalar_t__ hx711_reset (struct hx711_data*) ; 
 int hx711_set_gain_for_channel (struct hx711_data*,int) ; 

__attribute__((used)) static int hx711_reset_read(struct hx711_data *hx711_data, int chan)
{
	int ret;
	int val;

	/*
	 * hx711_reset() must be called from here
	 * because it could be calling hx711_read() by itself
	 */
	if (hx711_reset(hx711_data)) {
		dev_err(hx711_data->dev, "reset failed!");
		return -EIO;
	}

	ret = hx711_set_gain_for_channel(hx711_data, chan);
	if (ret < 0)
		return ret;

	val = hx711_read(hx711_data);

	return val;
}
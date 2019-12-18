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
struct ltc2978_data {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTC3880_MFR_CLEAR_PEAKS ; 
 int /*<<< orphan*/  PMBUS_CLEAR_FAULTS ; 
 scalar_t__ has_clear_peaks (struct ltc2978_data*) ; 
 int ltc_write_byte (struct i2c_client*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltc2978_clear_peaks(struct ltc2978_data *data,
			       struct i2c_client *client, int page)
{
	int ret;

	if (has_clear_peaks(data))
		ret = ltc_write_byte(client, 0, LTC3880_MFR_CLEAR_PEAKS);
	else
		ret = ltc_write_byte(client, page, PMBUS_CLEAR_FAULTS);

	return ret;
}
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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TMP006_DEVICE_ID ; 
 int TMP006_DEVICE_MAGIC ; 
 int /*<<< orphan*/  TMP006_MANUFACTURER_ID ; 
 int TMP006_MANUFACTURER_MAGIC ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tmp006_check_identification(struct i2c_client *client)
{
	int mid, did;

	mid = i2c_smbus_read_word_swapped(client, TMP006_MANUFACTURER_ID);
	if (mid < 0)
		return false;

	did = i2c_smbus_read_word_swapped(client, TMP006_DEVICE_ID);
	if (did < 0)
		return false;

	return mid == TMP006_MANUFACTURER_MAGIC && did == TMP006_DEVICE_MAGIC;
}
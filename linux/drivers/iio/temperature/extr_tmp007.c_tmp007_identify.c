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
 int /*<<< orphan*/  TMP007_DEVICE_ID ; 
 int TMP007_DEVICE_MAGIC ; 
 int /*<<< orphan*/  TMP007_MANUFACTURER_ID ; 
 int TMP007_MANUFACTURER_MAGIC ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tmp007_identify(struct i2c_client *client)
{
	int manf_id, dev_id;

	manf_id = i2c_smbus_read_word_swapped(client, TMP007_MANUFACTURER_ID);
	if (manf_id < 0)
		return false;

	dev_id = i2c_smbus_read_word_swapped(client, TMP007_DEVICE_ID);
	if (dev_id < 0)
		return false;

	return (manf_id == TMP007_MANUFACTURER_MAGIC && dev_id == TMP007_DEVICE_MAGIC);
}
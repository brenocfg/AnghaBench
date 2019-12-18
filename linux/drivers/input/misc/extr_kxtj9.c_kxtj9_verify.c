#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kxtj9_data {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  WHO_AM_I ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kxtj9_device_power_off (struct kxtj9_data*) ; 
 int kxtj9_device_power_on (struct kxtj9_data*) ; 

__attribute__((used)) static int kxtj9_verify(struct kxtj9_data *tj9)
{
	int retval;

	retval = kxtj9_device_power_on(tj9);
	if (retval < 0)
		return retval;

	retval = i2c_smbus_read_byte_data(tj9->client, WHO_AM_I);
	if (retval < 0) {
		dev_err(&tj9->client->dev, "read err int source\n");
		goto out;
	}

	retval = (retval != 0x07 && retval != 0x08) ? -EIO : 0;

out:
	kxtj9_device_power_off(tj9);
	return retval;
}
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
typedef  int u8 ;
struct kmx61_data {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int KMX61_ACC ; 
 int KMX61_ACC_STBY_BIT ; 
 int KMX61_MAG ; 
 int KMX61_MAG_STBY_BIT ; 
 int /*<<< orphan*/  KMX61_REG_STBY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kmx61_get_mode(struct kmx61_data *data, u8 *mode, u8 device)
{
	int ret;

	ret = i2c_smbus_read_byte_data(data->client, KMX61_REG_STBY);
	if (ret < 0) {
		dev_err(&data->client->dev, "Error reading reg_stby\n");
		return ret;
	}
	*mode = 0;

	if (device & KMX61_ACC) {
		if (ret & KMX61_ACC_STBY_BIT)
			*mode |= KMX61_ACC_STBY_BIT;
		else
			*mode &= ~KMX61_ACC_STBY_BIT;
	}

	if (device & KMX61_MAG) {
		if (ret & KMX61_MAG_STBY_BIT)
			*mode |= KMX61_MAG_STBY_BIT;
		else
			*mode &= ~KMX61_MAG_STBY_BIT;
	}

	return 0;
}
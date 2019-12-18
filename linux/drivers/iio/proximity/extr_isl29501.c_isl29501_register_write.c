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
typedef  int u32 ;
struct isl29501_register_desc {scalar_t__ lsb; scalar_t__ msb; } ;
struct isl29501_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;
typedef  enum isl29501_register_name { ____Placeholder_isl29501_register_name } isl29501_register_name ;

/* Variables and functions */
 int ERANGE ; 
 int U16_MAX ; 
 int U8_MAX ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct isl29501_register_desc* isl29501_registers ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 isl29501_register_write(struct isl29501_private *isl29501,
				   enum isl29501_register_name name,
				   u32 value)
{
	const struct isl29501_register_desc *reg = &isl29501_registers[name];
	int ret;

	if (!reg->msb && value > U8_MAX)
		return -ERANGE;

	if (value > U16_MAX)
		return -ERANGE;

	mutex_lock(&isl29501->lock);
	if (reg->msb) {
		ret = i2c_smbus_write_byte_data(isl29501->client,
						reg->msb, value >> 8);
		if (ret < 0)
			goto err;
	}

	ret = i2c_smbus_write_byte_data(isl29501->client, reg->lsb, value);

err:
	mutex_unlock(&isl29501->lock);
	return ret;
}
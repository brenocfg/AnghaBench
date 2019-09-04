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
typedef  int u8 ;
typedef  int u32 ;
struct isl29501_register_desc {scalar_t__ lsb; scalar_t__ msb; } ;
struct isl29501_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;
typedef  scalar_t__ s32 ;
typedef  enum isl29501_register_name { ____Placeholder_isl29501_register_name } isl29501_register_name ;

/* Variables and functions */
 scalar_t__ i2c_smbus_read_byte_data (int /*<<< orphan*/ ,scalar_t__) ; 
 struct isl29501_register_desc* isl29501_registers ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int isl29501_register_read(struct isl29501_private *isl29501,
				  enum isl29501_register_name name,
				  u32 *val)
{
	const struct isl29501_register_desc *reg = &isl29501_registers[name];
	u8 msb = 0, lsb = 0;
	s32 ret;

	mutex_lock(&isl29501->lock);
	if (reg->msb) {
		ret = i2c_smbus_read_byte_data(isl29501->client, reg->msb);
		if (ret < 0)
			goto err;
		msb = ret;
	}

	if (reg->lsb) {
		ret = i2c_smbus_read_byte_data(isl29501->client, reg->lsb);
		if (ret < 0)
			goto err;
		lsb = ret;
	}
	mutex_unlock(&isl29501->lock);

	*val = (msb << 8) + lsb;

	return 0;
err:
	mutex_unlock(&isl29501->lock);

	return ret;
}
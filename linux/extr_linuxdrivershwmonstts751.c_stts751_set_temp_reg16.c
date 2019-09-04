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
typedef  int /*<<< orphan*/  u8 ;
struct stts751_priv {int /*<<< orphan*/  client; } ;
typedef  int s32 ;

/* Variables and functions */
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stts751_to_hw (int) ; 

__attribute__((used)) static int stts751_set_temp_reg16(struct stts751_priv *priv, int temp,
				  u8 hreg, u8 lreg)
{
	s32 hwval;
	int ret;

	hwval = stts751_to_hw(temp);

	ret = i2c_smbus_write_byte_data(priv->client, hreg, hwval >> 8);
	if (ret)
		return ret;

	return i2c_smbus_write_byte_data(priv->client, lreg, hwval & 0xff);
}
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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  reg ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int i2c_smbus_write_word_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int retu_regmap_write(void *context, const void *data, size_t count)
{
	u8 reg;
	u16 val;
	struct device *dev = context;
	struct i2c_client *i2c = to_i2c_client(dev);

	BUG_ON(count != sizeof(reg) + sizeof(val));
	memcpy(&reg, data, sizeof(reg));
	memcpy(&val, data + sizeof(reg), sizeof(val));
	return i2c_smbus_write_word_data(i2c, reg, val);
}
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
typedef  size_t u8 ;
struct i2c_client {int dummy; } ;
struct bt819 {size_t* reg; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int i2c_smbus_write_byte_data (struct i2c_client*,size_t,size_t) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int bt819_write(struct bt819 *decoder, u8 reg, u8 value)
{
	struct i2c_client *client = v4l2_get_subdevdata(&decoder->sd);

	decoder->reg[reg] = value;
	return i2c_smbus_write_byte_data(client, reg, value);
}
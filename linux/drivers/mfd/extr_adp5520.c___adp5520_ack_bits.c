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
typedef  int /*<<< orphan*/  uint8_t ;
struct i2c_client {int dummy; } ;
struct adp5520_chip {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __adp5520_read (struct i2c_client*,int,int /*<<< orphan*/ *) ; 
 int __adp5520_write (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 struct adp5520_chip* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __adp5520_ack_bits(struct i2c_client *client, int reg,
			      uint8_t bit_mask)
{
	struct adp5520_chip *chip = i2c_get_clientdata(client);
	uint8_t reg_val;
	int ret;

	mutex_lock(&chip->lock);

	ret = __adp5520_read(client, reg, &reg_val);

	if (!ret) {
		reg_val |= bit_mask;
		ret = __adp5520_write(client, reg, reg_val);
	}

	mutex_unlock(&chip->lock);
	return ret;
}
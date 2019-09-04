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
struct nau7802_state {int /*<<< orphan*/  lock; int /*<<< orphan*/  client; scalar_t__ conversion_count; } ;

/* Variables and functions */
 int NAU7802_CTRL1_GAINS_BITS ; 
 int /*<<< orphan*/  NAU7802_REG_CTRL1 ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nau7802_set_gain(struct nau7802_state *st, int gain)
{
	int ret;

	mutex_lock(&st->lock);
	st->conversion_count = 0;

	ret = i2c_smbus_read_byte_data(st->client, NAU7802_REG_CTRL1);
	if (ret < 0)
		goto nau7802_sysfs_set_gain_out;
	ret = i2c_smbus_write_byte_data(st->client, NAU7802_REG_CTRL1,
					(ret & (~NAU7802_CTRL1_GAINS_BITS)) |
					gain);

nau7802_sysfs_set_gain_out:
	mutex_unlock(&st->lock);

	return ret;
}
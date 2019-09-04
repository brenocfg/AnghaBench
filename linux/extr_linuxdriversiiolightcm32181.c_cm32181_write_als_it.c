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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int dummy; } ;
struct cm32181_chip {int /*<<< orphan*/  lock; int /*<<< orphan*/ * conf_regs; struct i2c_client* client; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  CM32181_CMD_ALS_IT_MASK ; 
 int /*<<< orphan*/  CM32181_CMD_ALS_IT_SHIFT ; 
 size_t CM32181_REG_ADDR_CMD ; 
 int /*<<< orphan*/ * als_it_bits ; 
 int* als_it_value ; 
 int i2c_smbus_write_word_data (struct i2c_client*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cm32181_write_als_it(struct cm32181_chip *cm32181, int val)
{
	struct i2c_client *client = cm32181->client;
	u16 als_it;
	int ret, i, n;

	n = ARRAY_SIZE(als_it_value);
	for (i = 0; i < n; i++)
		if (val <= als_it_value[i])
			break;
	if (i >= n)
		i = n - 1;

	als_it = als_it_bits[i];
	als_it <<= CM32181_CMD_ALS_IT_SHIFT;

	mutex_lock(&cm32181->lock);
	cm32181->conf_regs[CM32181_REG_ADDR_CMD] &=
		~CM32181_CMD_ALS_IT_MASK;
	cm32181->conf_regs[CM32181_REG_ADDR_CMD] |=
		als_it;
	ret = i2c_smbus_write_word_data(client, CM32181_REG_ADDR_CMD,
			cm32181->conf_regs[CM32181_REG_ADDR_CMD]);
	mutex_unlock(&cm32181->lock);

	return ret;
}
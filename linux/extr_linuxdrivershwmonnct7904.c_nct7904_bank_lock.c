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
struct nct7904_data {unsigned int bank_sel; int /*<<< orphan*/  client; int /*<<< orphan*/  bank_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANK_SEL_REG ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nct7904_bank_lock(struct nct7904_data *data, unsigned int bank)
{
	int ret;

	mutex_lock(&data->bank_lock);
	if (data->bank_sel == bank)
		return 0;
	ret = i2c_smbus_write_byte_data(data->client, BANK_SEL_REG, bank);
	if (ret == 0)
		data->bank_sel = bank;
	else
		data->bank_sel = -1;
	return ret;
}
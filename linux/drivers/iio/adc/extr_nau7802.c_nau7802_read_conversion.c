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
struct nau7802_state {int last_value; int /*<<< orphan*/  data_lock; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAU7802_REG_ADC_B0 ; 
 int /*<<< orphan*/  NAU7802_REG_ADC_B1 ; 
 int /*<<< orphan*/  NAU7802_REG_ADC_B2 ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sign_extend32 (int,int) ; 

__attribute__((used)) static int nau7802_read_conversion(struct nau7802_state *st)
{
	int data;

	mutex_lock(&st->data_lock);
	data = i2c_smbus_read_byte_data(st->client, NAU7802_REG_ADC_B2);
	if (data < 0)
		goto nau7802_read_conversion_out;
	st->last_value = data << 16;

	data = i2c_smbus_read_byte_data(st->client, NAU7802_REG_ADC_B1);
	if (data < 0)
		goto nau7802_read_conversion_out;
	st->last_value |= data << 8;

	data = i2c_smbus_read_byte_data(st->client, NAU7802_REG_ADC_B0);
	if (data < 0)
		goto nau7802_read_conversion_out;
	st->last_value |= data;

	st->last_value = sign_extend32(st->last_value, 23);

nau7802_read_conversion_out:
	mutex_unlock(&st->data_lock);

	return data;
}
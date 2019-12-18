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
struct pcf8591_data {int /*<<< orphan*/  aout; int /*<<< orphan*/  control; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCF8591_INIT_AOUT ; 
 int /*<<< orphan*/  PCF8591_INIT_CONTROL ; 
 struct pcf8591_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_read_byte (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcf8591_init_client(struct i2c_client *client)
{
	struct pcf8591_data *data = i2c_get_clientdata(client);
	data->control = PCF8591_INIT_CONTROL;
	data->aout = PCF8591_INIT_AOUT;

	i2c_smbus_write_byte_data(client, data->control, data->aout);

	/*
	 * The first byte transmitted contains the conversion code of the
	 * previous read cycle. FLUSH IT!
	 */
	i2c_smbus_read_byte(client);
}
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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ltc_wait_ready (struct i2c_client*) ; 
 int pmbus_read_word_data (struct i2c_client*,int,int) ; 

__attribute__((used)) static int ltc_read_word_data(struct i2c_client *client, int page, int reg)
{
	int ret;

	ret = ltc_wait_ready(client);
	if (ret < 0)
		return ret;

	return pmbus_read_word_data(client, page, reg);
}
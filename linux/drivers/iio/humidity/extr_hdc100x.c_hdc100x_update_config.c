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
struct hdc100x_data {int config; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDC100X_REG_CONFIG ; 
 int i2c_smbus_write_word_swapped (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hdc100x_update_config(struct hdc100x_data *data, int mask, int val)
{
	int tmp = (~mask & data->config) | val;
	int ret;

	ret = i2c_smbus_write_word_swapped(data->client,
						HDC100X_REG_CONFIG, tmp);
	if (!ret)
		data->config = tmp;

	return ret;
}
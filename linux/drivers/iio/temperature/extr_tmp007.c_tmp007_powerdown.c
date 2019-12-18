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
struct tmp007_data {int config; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  TMP007_CONFIG ; 
 int TMP007_CONFIG_CONV_EN ; 
 int i2c_smbus_write_word_swapped (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tmp007_powerdown(struct tmp007_data *data)
{
	return i2c_smbus_write_word_swapped(data->client, TMP007_CONFIG,
			data->config & ~TMP007_CONFIG_CONV_EN);
}
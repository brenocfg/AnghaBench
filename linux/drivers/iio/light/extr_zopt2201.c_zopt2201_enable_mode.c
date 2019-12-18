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
typedef  int /*<<< orphan*/  u8 ;
struct zopt2201_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZOPT2201_MAIN_CTRL ; 
 int /*<<< orphan*/  ZOPT2201_MAIN_CTRL_LS_EN ; 
 int /*<<< orphan*/  ZOPT2201_MAIN_CTRL_LS_MODE ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zopt2201_enable_mode(struct zopt2201_data *data, bool uvb_mode)
{
	u8 out = ZOPT2201_MAIN_CTRL_LS_EN;

	if (uvb_mode)
		out |= ZOPT2201_MAIN_CTRL_LS_MODE;

	return i2c_smbus_write_byte_data(data->client, ZOPT2201_MAIN_CTRL, out);
}
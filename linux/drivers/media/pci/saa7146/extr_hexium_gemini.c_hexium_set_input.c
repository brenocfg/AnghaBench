#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union i2c_smbus_data {int /*<<< orphan*/  byte; } ;
struct hexium {int /*<<< orphan*/  i2c_adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  adr; int /*<<< orphan*/  byte; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_D (char*) ; 
 int /*<<< orphan*/  I2C_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_SMBUS_WRITE ; 
 TYPE_1__* hexium_input_select ; 
 scalar_t__ i2c_smbus_xfer (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union i2c_smbus_data*) ; 

__attribute__((used)) static int hexium_set_input(struct hexium *hexium, int input)
{
	union i2c_smbus_data data;

	DEB_D("\n");

	data.byte = hexium_input_select[input].byte;
	if (0 != i2c_smbus_xfer(&hexium->i2c_adapter, 0x6c, 0, I2C_SMBUS_WRITE, hexium_input_select[input].adr, I2C_SMBUS_BYTE_DATA, &data)) {
		return -1;
	}

	return 0;
}
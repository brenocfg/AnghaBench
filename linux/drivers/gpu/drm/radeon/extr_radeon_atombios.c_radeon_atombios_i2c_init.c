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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u8 ;
struct radeon_i2c_bus_rec {int i2c_id; scalar_t__ valid; } ;
struct TYPE_2__ {struct atom_context* atom_context; } ;
struct radeon_device {int /*<<< orphan*/  ddev; int /*<<< orphan*/ * i2c_bus; TYPE_1__ mode_info; } ;
struct atom_context {int bios; } ;
struct _ATOM_GPIO_I2C_INFO {int /*<<< orphan*/ * asGPIO_Info; } ;
typedef  int /*<<< orphan*/  ATOM_GPIO_I2C_ASSIGMENT ;
typedef  int /*<<< orphan*/  ATOM_COMMON_TABLE_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  GPIO_I2C_Info ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atom_parse_data_header (struct atom_context*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 struct radeon_i2c_bus_rec radeon_get_bus_rec_for_i2c_gpio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_i2c_create (int /*<<< orphan*/ ,struct radeon_i2c_bus_rec*,char*) ; 
 int /*<<< orphan*/  radeon_lookup_i2c_gpio_quirks (struct radeon_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void radeon_atombios_i2c_init(struct radeon_device *rdev)
{
	struct atom_context *ctx = rdev->mode_info.atom_context;
	ATOM_GPIO_I2C_ASSIGMENT *gpio;
	struct radeon_i2c_bus_rec i2c;
	int index = GetIndexIntoMasterTable(DATA, GPIO_I2C_Info);
	struct _ATOM_GPIO_I2C_INFO *i2c_info;
	uint16_t data_offset, size;
	int i, num_indices;
	char stmp[32];

	if (atom_parse_data_header(ctx, index, &size, NULL, NULL, &data_offset)) {
		i2c_info = (struct _ATOM_GPIO_I2C_INFO *)(ctx->bios + data_offset);

		num_indices = (size - sizeof(ATOM_COMMON_TABLE_HEADER)) /
			sizeof(ATOM_GPIO_I2C_ASSIGMENT);

		gpio = &i2c_info->asGPIO_Info[0];
		for (i = 0; i < num_indices; i++) {
			radeon_lookup_i2c_gpio_quirks(rdev, gpio, i);

			i2c = radeon_get_bus_rec_for_i2c_gpio(gpio);

			if (i2c.valid) {
				sprintf(stmp, "0x%x", i2c.i2c_id);
				rdev->i2c_bus[i] = radeon_i2c_create(rdev->ddev, &i2c, stmp);
			}
			gpio = (ATOM_GPIO_I2C_ASSIGMENT *)
				((u8 *)gpio + sizeof(ATOM_GPIO_I2C_ASSIGMENT));
		}
	}
}
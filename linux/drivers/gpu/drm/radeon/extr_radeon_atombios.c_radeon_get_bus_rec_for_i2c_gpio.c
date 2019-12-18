#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct radeon_i2c_bus_rec {int mask_clk_reg; int mask_data_reg; int en_clk_reg; int en_data_reg; int y_clk_reg; int y_data_reg; int a_clk_reg; int a_data_reg; int mask_clk_mask; int mask_data_mask; int en_clk_mask; int en_data_mask; int y_clk_mask; int y_data_mask; int a_clk_mask; int a_data_mask; int hw_capable; int mm_i2c; int i2c_id; int valid; } ;
struct TYPE_5__ {scalar_t__ bfHW_Capable; } ;
struct TYPE_6__ {int ucAccess; TYPE_1__ sbfAccess; } ;
struct TYPE_7__ {int ucClkMaskShift; int ucDataMaskShift; int ucClkEnShift; int ucDataEnShift; int ucClkY_Shift; int ucDataY_Shift; int ucClkA_Shift; int ucDataA_Shift; TYPE_2__ sucI2cId; int /*<<< orphan*/  usDataA_RegisterIndex; int /*<<< orphan*/  usClkA_RegisterIndex; int /*<<< orphan*/  usDataY_RegisterIndex; int /*<<< orphan*/  usClkY_RegisterIndex; int /*<<< orphan*/  usDataEnRegisterIndex; int /*<<< orphan*/  usClkEnRegisterIndex; int /*<<< orphan*/  usDataMaskRegisterIndex; int /*<<< orphan*/  usClkMaskRegisterIndex; } ;
typedef  TYPE_3__ ATOM_GPIO_I2C_ASSIGMENT ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct radeon_i2c_bus_rec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct radeon_i2c_bus_rec radeon_get_bus_rec_for_i2c_gpio(ATOM_GPIO_I2C_ASSIGMENT *gpio)
{
	struct radeon_i2c_bus_rec i2c;

	memset(&i2c, 0, sizeof(struct radeon_i2c_bus_rec));

	i2c.mask_clk_reg = le16_to_cpu(gpio->usClkMaskRegisterIndex) * 4;
	i2c.mask_data_reg = le16_to_cpu(gpio->usDataMaskRegisterIndex) * 4;
	i2c.en_clk_reg = le16_to_cpu(gpio->usClkEnRegisterIndex) * 4;
	i2c.en_data_reg = le16_to_cpu(gpio->usDataEnRegisterIndex) * 4;
	i2c.y_clk_reg = le16_to_cpu(gpio->usClkY_RegisterIndex) * 4;
	i2c.y_data_reg = le16_to_cpu(gpio->usDataY_RegisterIndex) * 4;
	i2c.a_clk_reg = le16_to_cpu(gpio->usClkA_RegisterIndex) * 4;
	i2c.a_data_reg = le16_to_cpu(gpio->usDataA_RegisterIndex) * 4;
	i2c.mask_clk_mask = (1 << gpio->ucClkMaskShift);
	i2c.mask_data_mask = (1 << gpio->ucDataMaskShift);
	i2c.en_clk_mask = (1 << gpio->ucClkEnShift);
	i2c.en_data_mask = (1 << gpio->ucDataEnShift);
	i2c.y_clk_mask = (1 << gpio->ucClkY_Shift);
	i2c.y_data_mask = (1 << gpio->ucDataY_Shift);
	i2c.a_clk_mask = (1 << gpio->ucClkA_Shift);
	i2c.a_data_mask = (1 << gpio->ucDataA_Shift);

	if (gpio->sucI2cId.sbfAccess.bfHW_Capable)
		i2c.hw_capable = true;
	else
		i2c.hw_capable = false;

	if (gpio->sucI2cId.ucAccess == 0xa0)
		i2c.mm_i2c = true;
	else
		i2c.mm_i2c = false;

	i2c.i2c_id = gpio->sucI2cId.ucAccess;

	if (i2c.mask_clk_reg)
		i2c.valid = true;
	else
		i2c.valid = false;

	return i2c;
}
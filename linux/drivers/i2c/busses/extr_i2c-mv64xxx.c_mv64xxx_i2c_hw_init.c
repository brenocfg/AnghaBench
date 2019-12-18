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
struct TYPE_2__ {scalar_t__ control; scalar_t__ ext_addr; scalar_t__ addr; scalar_t__ clock; scalar_t__ soft_reset; } ;
struct mv64xxx_i2c_data {int /*<<< orphan*/  state; TYPE_1__ reg_offsets; scalar_t__ reg_base; int /*<<< orphan*/  freq_n; int /*<<< orphan*/  freq_m; scalar_t__ offload_enabled; } ;

/* Variables and functions */
 int MV64XXX_I2C_BAUD_DIV_M (int /*<<< orphan*/ ) ; 
 int MV64XXX_I2C_BAUD_DIV_N (int /*<<< orphan*/ ) ; 
 scalar_t__ MV64XXX_I2C_REG_BRIDGE_CONTROL ; 
 scalar_t__ MV64XXX_I2C_REG_BRIDGE_INTR_CAUSE ; 
 scalar_t__ MV64XXX_I2C_REG_BRIDGE_INTR_MASK ; 
 scalar_t__ MV64XXX_I2C_REG_BRIDGE_TIMING ; 
 int MV64XXX_I2C_REG_CONTROL_STOP ; 
 int MV64XXX_I2C_REG_CONTROL_TWSIEN ; 
 int /*<<< orphan*/  MV64XXX_I2C_STATE_IDLE ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void
mv64xxx_i2c_hw_init(struct mv64xxx_i2c_data *drv_data)
{
	if (drv_data->offload_enabled) {
		writel(0, drv_data->reg_base + MV64XXX_I2C_REG_BRIDGE_CONTROL);
		writel(0, drv_data->reg_base + MV64XXX_I2C_REG_BRIDGE_TIMING);
		writel(0, drv_data->reg_base +
			MV64XXX_I2C_REG_BRIDGE_INTR_CAUSE);
		writel(0, drv_data->reg_base +
			MV64XXX_I2C_REG_BRIDGE_INTR_MASK);
	}

	writel(0, drv_data->reg_base + drv_data->reg_offsets.soft_reset);
	writel(MV64XXX_I2C_BAUD_DIV_M(drv_data->freq_m) | MV64XXX_I2C_BAUD_DIV_N(drv_data->freq_n),
		drv_data->reg_base + drv_data->reg_offsets.clock);
	writel(0, drv_data->reg_base + drv_data->reg_offsets.addr);
	writel(0, drv_data->reg_base + drv_data->reg_offsets.ext_addr);
	writel(MV64XXX_I2C_REG_CONTROL_TWSIEN | MV64XXX_I2C_REG_CONTROL_STOP,
		drv_data->reg_base + drv_data->reg_offsets.control);
	drv_data->state = MV64XXX_I2C_STATE_IDLE;
}
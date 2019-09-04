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
typedef  int uint32_t ;
struct i2c_adapter {int dummy; } ;
struct amdgpu_i2c_bus_rec {int a_clk_mask; int a_data_mask; int en_clk_mask; int en_data_mask; int mask_clk_mask; int mask_data_mask; int /*<<< orphan*/  mask_data_reg; int /*<<< orphan*/  mask_clk_reg; int /*<<< orphan*/  en_data_reg; int /*<<< orphan*/  en_clk_reg; int /*<<< orphan*/  a_data_reg; int /*<<< orphan*/  a_clk_reg; scalar_t__ hw_capable; } ;
struct amdgpu_i2c_chan {int /*<<< orphan*/  mutex; struct amdgpu_i2c_bus_rec rec; TYPE_1__* dev; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {struct amdgpu_device* dev_private; } ;

/* Variables and functions */
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 struct amdgpu_i2c_chan* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_i2c_pre_xfer(struct i2c_adapter *i2c_adap)
{
	struct amdgpu_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	struct amdgpu_device *adev = i2c->dev->dev_private;
	struct amdgpu_i2c_bus_rec *rec = &i2c->rec;
	uint32_t temp;

	mutex_lock(&i2c->mutex);

	/* switch the pads to ddc mode */
	if (rec->hw_capable) {
		temp = RREG32(rec->mask_clk_reg);
		temp &= ~(1 << 16);
		WREG32(rec->mask_clk_reg, temp);
	}

	/* clear the output pin values */
	temp = RREG32(rec->a_clk_reg) & ~rec->a_clk_mask;
	WREG32(rec->a_clk_reg, temp);

	temp = RREG32(rec->a_data_reg) & ~rec->a_data_mask;
	WREG32(rec->a_data_reg, temp);

	/* set the pins to input */
	temp = RREG32(rec->en_clk_reg) & ~rec->en_clk_mask;
	WREG32(rec->en_clk_reg, temp);

	temp = RREG32(rec->en_data_reg) & ~rec->en_data_mask;
	WREG32(rec->en_data_reg, temp);

	/* mask the gpio pins for software use */
	temp = RREG32(rec->mask_clk_reg) | rec->mask_clk_mask;
	WREG32(rec->mask_clk_reg, temp);
	temp = RREG32(rec->mask_clk_reg);

	temp = RREG32(rec->mask_data_reg) | rec->mask_data_mask;
	WREG32(rec->mask_data_reg, temp);
	temp = RREG32(rec->mask_data_reg);

	return 0;
}
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
typedef  scalar_t__ u32 ;
struct radeon_i2c_bus_rec {scalar_t__ a_clk_reg; scalar_t__ mask_clk_reg; int a_clk_mask; scalar_t__ a_data_reg; int a_data_mask; scalar_t__ en_clk_reg; int en_clk_mask; scalar_t__ en_data_reg; int en_data_mask; int mask_clk_mask; scalar_t__ mask_data_reg; int mask_data_mask; scalar_t__ hw_capable; } ;
struct radeon_i2c_chan {int /*<<< orphan*/  mutex; struct radeon_i2c_bus_rec rec; TYPE_1__* dev; } ;
struct radeon_device {scalar_t__ family; int /*<<< orphan*/  dc_hw_i2c_mutex; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_2__ {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_IS_AVIVO (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE3 (struct radeon_device*) ; 
 scalar_t__ CHIP_R200 ; 
 scalar_t__ CHIP_R300 ; 
 scalar_t__ CHIP_R350 ; 
 scalar_t__ CHIP_RV350 ; 
 int R200_DVI_I2C_PIN_SEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R200_SEL_DDC1 ; 
 int /*<<< orphan*/  R200_SEL_DDC3 ; 
 scalar_t__ RADEON_DVI_I2C_CNTL_0 ; 
 scalar_t__ RADEON_GPIO_CRT2_DDC ; 
 scalar_t__ RADEON_GPIO_DVI_DDC ; 
 scalar_t__ RADEON_GPIO_MONID ; 
 int RADEON_I2C_SOFT_RST ; 
 int RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 struct radeon_i2c_chan* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pre_xfer(struct i2c_adapter *i2c_adap)
{
	struct radeon_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	struct radeon_device *rdev = i2c->dev->dev_private;
	struct radeon_i2c_bus_rec *rec = &i2c->rec;
	uint32_t temp;

	mutex_lock(&i2c->mutex);

	/* RV410 appears to have a bug where the hw i2c in reset
	 * holds the i2c port in a bad state - switch hw i2c away before
	 * doing DDC - do this for all r200s/r300s/r400s for safety sake
	 */
	if (rec->hw_capable) {
		if ((rdev->family >= CHIP_R200) && !ASIC_IS_AVIVO(rdev)) {
			u32 reg;

			if (rdev->family >= CHIP_RV350)
				reg = RADEON_GPIO_MONID;
			else if ((rdev->family == CHIP_R300) ||
				 (rdev->family == CHIP_R350))
				reg = RADEON_GPIO_DVI_DDC;
			else
				reg = RADEON_GPIO_CRT2_DDC;

			mutex_lock(&rdev->dc_hw_i2c_mutex);
			if (rec->a_clk_reg == reg) {
				WREG32(RADEON_DVI_I2C_CNTL_0, (RADEON_I2C_SOFT_RST |
							       R200_DVI_I2C_PIN_SEL(R200_SEL_DDC1)));
			} else {
				WREG32(RADEON_DVI_I2C_CNTL_0, (RADEON_I2C_SOFT_RST |
							       R200_DVI_I2C_PIN_SEL(R200_SEL_DDC3)));
			}
			mutex_unlock(&rdev->dc_hw_i2c_mutex);
		}
	}

	/* switch the pads to ddc mode */
	if (ASIC_IS_DCE3(rdev) && rec->hw_capable) {
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
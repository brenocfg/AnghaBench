#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct radeon_i2c_bus_rec {int mask_clk_reg; int mask_clk_mask; int mask_data_reg; int mask_data_mask; int a_clk_reg; int a_clk_mask; int a_data_reg; int a_data_mask; int en_clk_reg; int en_clk_mask; int en_data_reg; int en_data_mask; } ;
struct radeon_i2c_chan {struct radeon_i2c_bus_rec rec; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct radeon_device {int /*<<< orphan*/  dc_hw_i2c_mutex; TYPE_2__ pm; } ;
struct i2c_msg {int len; int addr; int flags; int* buf; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_3__ {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int ATOM_S6_HW_I2C_BUSY_STATE ; 
#define  AVIVO_DC_GPIO_DDC1_MASK 130 
#define  AVIVO_DC_GPIO_DDC2_MASK 129 
#define  AVIVO_DC_GPIO_DDC3_MASK 128 
 int AVIVO_DC_I2C_ABORT ; 
 int AVIVO_DC_I2C_ADDR_COUNT (int) ; 
 int AVIVO_DC_I2C_ARBITRATION ; 
 int AVIVO_DC_I2C_CONTROL1 ; 
 int AVIVO_DC_I2C_CONTROL2 ; 
 int AVIVO_DC_I2C_CONTROL3 ; 
 int AVIVO_DC_I2C_DATA ; 
 int AVIVO_DC_I2C_DATA_COUNT (int) ; 
 int AVIVO_DC_I2C_DONE ; 
 int AVIVO_DC_I2C_EN ; 
 int AVIVO_DC_I2C_GO ; 
 int AVIVO_DC_I2C_HALT ; 
 int AVIVO_DC_I2C_NACK ; 
 int AVIVO_DC_I2C_PIN_SELECT (int /*<<< orphan*/ ) ; 
 int AVIVO_DC_I2C_RECEIVE ; 
 int AVIVO_DC_I2C_RESET ; 
 int AVIVO_DC_I2C_SOFT_RESET ; 
 int AVIVO_DC_I2C_START ; 
 int AVIVO_DC_I2C_STATUS1 ; 
 int AVIVO_DC_I2C_STOP ; 
 int AVIVO_DC_I2C_SW_CAN_USE_I2C ; 
 int AVIVO_DC_I2C_SW_DONE_USING_I2C ; 
 int AVIVO_DC_I2C_SW_WANTS_TO_USE_I2C ; 
 int AVIVO_DC_I2C_TIME_LIMIT (int) ; 
 int /*<<< orphan*/  AVIVO_SEL_DDC1 ; 
 int /*<<< orphan*/  AVIVO_SEL_DDC2 ; 
 int /*<<< orphan*/  AVIVO_SEL_DDC3 ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int I2C_M_RD ; 
 int RADEON_BIOS_6_SCRATCH ; 
 int RREG32 (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 struct radeon_i2c_chan* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int radeon_get_i2c_prescale (struct radeon_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int r500_hw_i2c_xfer(struct i2c_adapter *i2c_adap,
			    struct i2c_msg *msgs, int num)
{
	struct radeon_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	struct radeon_device *rdev = i2c->dev->dev_private;
	struct radeon_i2c_bus_rec *rec = &i2c->rec;
	struct i2c_msg *p;
	int i, j, remaining, current_count, buffer_offset, ret = num;
	u32 prescale;
	u32 tmp, reg;
	u32 saved1, saved2;

	mutex_lock(&rdev->dc_hw_i2c_mutex);
	/* take the pm lock since we need a constant sclk */
	mutex_lock(&rdev->pm.mutex);

	prescale = radeon_get_i2c_prescale(rdev);

	/* clear gpio mask bits */
	tmp = RREG32(rec->mask_clk_reg);
	tmp &= ~rec->mask_clk_mask;
	WREG32(rec->mask_clk_reg, tmp);
	tmp = RREG32(rec->mask_clk_reg);

	tmp = RREG32(rec->mask_data_reg);
	tmp &= ~rec->mask_data_mask;
	WREG32(rec->mask_data_reg, tmp);
	tmp = RREG32(rec->mask_data_reg);

	/* clear pin values */
	tmp = RREG32(rec->a_clk_reg);
	tmp &= ~rec->a_clk_mask;
	WREG32(rec->a_clk_reg, tmp);
	tmp = RREG32(rec->a_clk_reg);

	tmp = RREG32(rec->a_data_reg);
	tmp &= ~rec->a_data_mask;
	WREG32(rec->a_data_reg, tmp);
	tmp = RREG32(rec->a_data_reg);

	/* set the pins to input */
	tmp = RREG32(rec->en_clk_reg);
	tmp &= ~rec->en_clk_mask;
	WREG32(rec->en_clk_reg, tmp);
	tmp = RREG32(rec->en_clk_reg);

	tmp = RREG32(rec->en_data_reg);
	tmp &= ~rec->en_data_mask;
	WREG32(rec->en_data_reg, tmp);
	tmp = RREG32(rec->en_data_reg);

	/* */
	tmp = RREG32(RADEON_BIOS_6_SCRATCH);
	WREG32(RADEON_BIOS_6_SCRATCH, tmp | ATOM_S6_HW_I2C_BUSY_STATE);
	saved1 = RREG32(AVIVO_DC_I2C_CONTROL1);
	saved2 = RREG32(0x494);
	WREG32(0x494, saved2 | 0x1);

	WREG32(AVIVO_DC_I2C_ARBITRATION, AVIVO_DC_I2C_SW_WANTS_TO_USE_I2C);
	for (i = 0; i < 50; i++) {
		udelay(1);
		if (RREG32(AVIVO_DC_I2C_ARBITRATION) & AVIVO_DC_I2C_SW_CAN_USE_I2C)
			break;
	}
	if (i == 50) {
		DRM_ERROR("failed to get i2c bus\n");
		ret = -EBUSY;
		goto done;
	}

	reg = AVIVO_DC_I2C_START | AVIVO_DC_I2C_STOP | AVIVO_DC_I2C_EN;
	switch (rec->mask_clk_reg) {
	case AVIVO_DC_GPIO_DDC1_MASK:
		reg |= AVIVO_DC_I2C_PIN_SELECT(AVIVO_SEL_DDC1);
		break;
	case AVIVO_DC_GPIO_DDC2_MASK:
		reg |= AVIVO_DC_I2C_PIN_SELECT(AVIVO_SEL_DDC2);
		break;
	case AVIVO_DC_GPIO_DDC3_MASK:
		reg |= AVIVO_DC_I2C_PIN_SELECT(AVIVO_SEL_DDC3);
		break;
	default:
		DRM_ERROR("gpio not supported with hw i2c\n");
		ret = -EINVAL;
		goto done;
	}

	/* check for bus probe */
	p = &msgs[0];
	if ((num == 1) && (p->len == 0)) {
		WREG32(AVIVO_DC_I2C_STATUS1, (AVIVO_DC_I2C_DONE |
					      AVIVO_DC_I2C_NACK |
					      AVIVO_DC_I2C_HALT));
		WREG32(AVIVO_DC_I2C_RESET, AVIVO_DC_I2C_SOFT_RESET);
		udelay(1);
		WREG32(AVIVO_DC_I2C_RESET, 0);

		WREG32(AVIVO_DC_I2C_DATA, (p->addr << 1) & 0xff);
		WREG32(AVIVO_DC_I2C_DATA, 0);

		WREG32(AVIVO_DC_I2C_CONTROL3, AVIVO_DC_I2C_TIME_LIMIT(48));
		WREG32(AVIVO_DC_I2C_CONTROL2, (AVIVO_DC_I2C_ADDR_COUNT(1) |
					       AVIVO_DC_I2C_DATA_COUNT(1) |
					       (prescale << 16)));
		WREG32(AVIVO_DC_I2C_CONTROL1, reg);
		WREG32(AVIVO_DC_I2C_STATUS1, AVIVO_DC_I2C_GO);
		for (j = 0; j < 200; j++) {
			udelay(50);
			tmp = RREG32(AVIVO_DC_I2C_STATUS1);
			if (tmp & AVIVO_DC_I2C_GO)
				continue;
			tmp = RREG32(AVIVO_DC_I2C_STATUS1);
			if (tmp & AVIVO_DC_I2C_DONE)
				break;
			else {
				DRM_DEBUG("i2c write error 0x%08x\n", tmp);
				WREG32(AVIVO_DC_I2C_RESET, AVIVO_DC_I2C_ABORT);
				ret = -EIO;
				goto done;
			}
		}
		goto done;
	}

	for (i = 0; i < num; i++) {
		p = &msgs[i];
		remaining = p->len;
		buffer_offset = 0;
		if (p->flags & I2C_M_RD) {
			while (remaining) {
				if (remaining > 15)
					current_count = 15;
				else
					current_count = remaining;
				WREG32(AVIVO_DC_I2C_STATUS1, (AVIVO_DC_I2C_DONE |
							      AVIVO_DC_I2C_NACK |
							      AVIVO_DC_I2C_HALT));
				WREG32(AVIVO_DC_I2C_RESET, AVIVO_DC_I2C_SOFT_RESET);
				udelay(1);
				WREG32(AVIVO_DC_I2C_RESET, 0);

				WREG32(AVIVO_DC_I2C_DATA, ((p->addr << 1) & 0xff) | 0x1);
				WREG32(AVIVO_DC_I2C_CONTROL3, AVIVO_DC_I2C_TIME_LIMIT(48));
				WREG32(AVIVO_DC_I2C_CONTROL2, (AVIVO_DC_I2C_ADDR_COUNT(1) |
							       AVIVO_DC_I2C_DATA_COUNT(current_count) |
							       (prescale << 16)));
				WREG32(AVIVO_DC_I2C_CONTROL1, reg | AVIVO_DC_I2C_RECEIVE);
				WREG32(AVIVO_DC_I2C_STATUS1, AVIVO_DC_I2C_GO);
				for (j = 0; j < 200; j++) {
					udelay(50);
					tmp = RREG32(AVIVO_DC_I2C_STATUS1);
					if (tmp & AVIVO_DC_I2C_GO)
						continue;
					tmp = RREG32(AVIVO_DC_I2C_STATUS1);
					if (tmp & AVIVO_DC_I2C_DONE)
						break;
					else {
						DRM_DEBUG("i2c read error 0x%08x\n", tmp);
						WREG32(AVIVO_DC_I2C_RESET, AVIVO_DC_I2C_ABORT);
						ret = -EIO;
						goto done;
					}
				}
				for (j = 0; j < current_count; j++)
					p->buf[buffer_offset + j] = RREG32(AVIVO_DC_I2C_DATA) & 0xff;
				remaining -= current_count;
				buffer_offset += current_count;
			}
		} else {
			while (remaining) {
				if (remaining > 15)
					current_count = 15;
				else
					current_count = remaining;
				WREG32(AVIVO_DC_I2C_STATUS1, (AVIVO_DC_I2C_DONE |
							      AVIVO_DC_I2C_NACK |
							      AVIVO_DC_I2C_HALT));
				WREG32(AVIVO_DC_I2C_RESET, AVIVO_DC_I2C_SOFT_RESET);
				udelay(1);
				WREG32(AVIVO_DC_I2C_RESET, 0);

				WREG32(AVIVO_DC_I2C_DATA, (p->addr << 1) & 0xff);
				for (j = 0; j < current_count; j++)
					WREG32(AVIVO_DC_I2C_DATA, p->buf[buffer_offset + j]);

				WREG32(AVIVO_DC_I2C_CONTROL3, AVIVO_DC_I2C_TIME_LIMIT(48));
				WREG32(AVIVO_DC_I2C_CONTROL2, (AVIVO_DC_I2C_ADDR_COUNT(1) |
							       AVIVO_DC_I2C_DATA_COUNT(current_count) |
							       (prescale << 16)));
				WREG32(AVIVO_DC_I2C_CONTROL1, reg);
				WREG32(AVIVO_DC_I2C_STATUS1, AVIVO_DC_I2C_GO);
				for (j = 0; j < 200; j++) {
					udelay(50);
					tmp = RREG32(AVIVO_DC_I2C_STATUS1);
					if (tmp & AVIVO_DC_I2C_GO)
						continue;
					tmp = RREG32(AVIVO_DC_I2C_STATUS1);
					if (tmp & AVIVO_DC_I2C_DONE)
						break;
					else {
						DRM_DEBUG("i2c write error 0x%08x\n", tmp);
						WREG32(AVIVO_DC_I2C_RESET, AVIVO_DC_I2C_ABORT);
						ret = -EIO;
						goto done;
					}
				}
				remaining -= current_count;
				buffer_offset += current_count;
			}
		}
	}

done:
	WREG32(AVIVO_DC_I2C_STATUS1, (AVIVO_DC_I2C_DONE |
				      AVIVO_DC_I2C_NACK |
				      AVIVO_DC_I2C_HALT));
	WREG32(AVIVO_DC_I2C_RESET, AVIVO_DC_I2C_SOFT_RESET);
	udelay(1);
	WREG32(AVIVO_DC_I2C_RESET, 0);

	WREG32(AVIVO_DC_I2C_ARBITRATION, AVIVO_DC_I2C_SW_DONE_USING_I2C);
	WREG32(AVIVO_DC_I2C_CONTROL1, saved1);
	WREG32(0x494, saved2);
	tmp = RREG32(RADEON_BIOS_6_SCRATCH);
	tmp &= ~ATOM_S6_HW_I2C_BUSY_STATE;
	WREG32(RADEON_BIOS_6_SCRATCH, tmp);

	mutex_unlock(&rdev->pm.mutex);
	mutex_unlock(&rdev->dc_hw_i2c_mutex);

	return ret;
}
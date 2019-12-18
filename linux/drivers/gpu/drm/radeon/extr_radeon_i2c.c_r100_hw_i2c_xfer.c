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
struct radeon_i2c_bus_rec {int /*<<< orphan*/  mask_clk_reg; scalar_t__ mm_i2c; } ;
struct radeon_i2c_chan {struct radeon_i2c_bus_rec rec; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct radeon_device {int family; int /*<<< orphan*/  dc_hw_i2c_mutex; TYPE_2__ pm; scalar_t__ is_atom_bios; } ;
struct i2c_msg {int len; int addr; int flags; int* buf; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_3__ {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int ATOM_S6_HW_I2C_BUSY_STATE ; 
#define  CHIP_R100 149 
#define  CHIP_R200 148 
#define  CHIP_R300 147 
#define  CHIP_R350 146 
#define  CHIP_R420 145 
#define  CHIP_R423 144 
#define  CHIP_RS100 143 
#define  CHIP_RS200 142 
#define  CHIP_RS300 141 
#define  CHIP_RS400 140 
#define  CHIP_RS480 139 
#define  CHIP_RV100 138 
#define  CHIP_RV200 137 
#define  CHIP_RV250 136 
#define  CHIP_RV280 135 
#define  CHIP_RV350 134 
#define  CHIP_RV380 133 
#define  CHIP_RV410 132 
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int EIO ; 
 int I2C_M_RD ; 
 int R200_DVI_I2C_PIN_SEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R200_SEL_DDC1 ; 
 int /*<<< orphan*/  R200_SEL_DDC2 ; 
 int /*<<< orphan*/  R200_SEL_DDC3 ; 
 int RADEON_BIOS_6_SCRATCH ; 
 int RADEON_DVI_I2C_CNTL_0 ; 
 int RADEON_DVI_I2C_CNTL_1 ; 
 int RADEON_DVI_I2C_DATA ; 
#define  RADEON_GPIO_CRT2_DDC 131 
#define  RADEON_GPIO_DVI_DDC 130 
#define  RADEON_GPIO_MONID 129 
#define  RADEON_GPIO_VGA_DDC 128 
 int RADEON_I2C_ABORT ; 
 int RADEON_I2C_ADDR_COUNT_SHIFT ; 
 int RADEON_I2C_CNTL_0 ; 
 int RADEON_I2C_CNTL_1 ; 
 int RADEON_I2C_DATA ; 
 int RADEON_I2C_DATA_COUNT_SHIFT ; 
 int RADEON_I2C_DONE ; 
 int RADEON_I2C_DRIVE_EN ; 
 int RADEON_I2C_EN ; 
 int RADEON_I2C_GO ; 
 int RADEON_I2C_HALT ; 
 int RADEON_I2C_NACK ; 
 int RADEON_I2C_PRESCALE_SHIFT ; 
 int RADEON_I2C_RECEIVE ; 
 int RADEON_I2C_SOFT_RST ; 
 int RADEON_I2C_START ; 
 int RADEON_I2C_STOP ; 
 int RADEON_I2C_TIME_LIMIT_SHIFT ; 
 int RREG32 (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 struct radeon_i2c_chan* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int radeon_get_i2c_prescale (struct radeon_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int r100_hw_i2c_xfer(struct i2c_adapter *i2c_adap,
			    struct i2c_msg *msgs, int num)
{
	struct radeon_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	struct radeon_device *rdev = i2c->dev->dev_private;
	struct radeon_i2c_bus_rec *rec = &i2c->rec;
	struct i2c_msg *p;
	int i, j, k, ret = num;
	u32 prescale;
	u32 i2c_cntl_0, i2c_cntl_1, i2c_data;
	u32 tmp, reg;

	mutex_lock(&rdev->dc_hw_i2c_mutex);
	/* take the pm lock since we need a constant sclk */
	mutex_lock(&rdev->pm.mutex);

	prescale = radeon_get_i2c_prescale(rdev);

	reg = ((prescale << RADEON_I2C_PRESCALE_SHIFT) |
	       RADEON_I2C_DRIVE_EN |
	       RADEON_I2C_START |
	       RADEON_I2C_STOP |
	       RADEON_I2C_GO);

	if (rdev->is_atom_bios) {
		tmp = RREG32(RADEON_BIOS_6_SCRATCH);
		WREG32(RADEON_BIOS_6_SCRATCH, tmp | ATOM_S6_HW_I2C_BUSY_STATE);
	}

	if (rec->mm_i2c) {
		i2c_cntl_0 = RADEON_I2C_CNTL_0;
		i2c_cntl_1 = RADEON_I2C_CNTL_1;
		i2c_data = RADEON_I2C_DATA;
	} else {
		i2c_cntl_0 = RADEON_DVI_I2C_CNTL_0;
		i2c_cntl_1 = RADEON_DVI_I2C_CNTL_1;
		i2c_data = RADEON_DVI_I2C_DATA;

		switch (rdev->family) {
		case CHIP_R100:
		case CHIP_RV100:
		case CHIP_RS100:
		case CHIP_RV200:
		case CHIP_RS200:
		case CHIP_RS300:
			switch (rec->mask_clk_reg) {
			case RADEON_GPIO_DVI_DDC:
				/* no gpio select bit */
				break;
			default:
				DRM_ERROR("gpio not supported with hw i2c\n");
				ret = -EINVAL;
				goto done;
			}
			break;
		case CHIP_R200:
			/* only bit 4 on r200 */
			switch (rec->mask_clk_reg) {
			case RADEON_GPIO_DVI_DDC:
				reg |= R200_DVI_I2C_PIN_SEL(R200_SEL_DDC1);
				break;
			case RADEON_GPIO_MONID:
				reg |= R200_DVI_I2C_PIN_SEL(R200_SEL_DDC3);
				break;
			default:
				DRM_ERROR("gpio not supported with hw i2c\n");
				ret = -EINVAL;
				goto done;
			}
			break;
		case CHIP_RV250:
		case CHIP_RV280:
			/* bits 3 and 4 */
			switch (rec->mask_clk_reg) {
			case RADEON_GPIO_DVI_DDC:
				reg |= R200_DVI_I2C_PIN_SEL(R200_SEL_DDC1);
				break;
			case RADEON_GPIO_VGA_DDC:
				reg |= R200_DVI_I2C_PIN_SEL(R200_SEL_DDC2);
				break;
			case RADEON_GPIO_CRT2_DDC:
				reg |= R200_DVI_I2C_PIN_SEL(R200_SEL_DDC3);
				break;
			default:
				DRM_ERROR("gpio not supported with hw i2c\n");
				ret = -EINVAL;
				goto done;
			}
			break;
		case CHIP_R300:
		case CHIP_R350:
			/* only bit 4 on r300/r350 */
			switch (rec->mask_clk_reg) {
			case RADEON_GPIO_VGA_DDC:
				reg |= R200_DVI_I2C_PIN_SEL(R200_SEL_DDC1);
				break;
			case RADEON_GPIO_DVI_DDC:
				reg |= R200_DVI_I2C_PIN_SEL(R200_SEL_DDC3);
				break;
			default:
				DRM_ERROR("gpio not supported with hw i2c\n");
				ret = -EINVAL;
				goto done;
			}
			break;
		case CHIP_RV350:
		case CHIP_RV380:
		case CHIP_R420:
		case CHIP_R423:
		case CHIP_RV410:
		case CHIP_RS400:
		case CHIP_RS480:
			/* bits 3 and 4 */
			switch (rec->mask_clk_reg) {
			case RADEON_GPIO_VGA_DDC:
				reg |= R200_DVI_I2C_PIN_SEL(R200_SEL_DDC1);
				break;
			case RADEON_GPIO_DVI_DDC:
				reg |= R200_DVI_I2C_PIN_SEL(R200_SEL_DDC2);
				break;
			case RADEON_GPIO_MONID:
				reg |= R200_DVI_I2C_PIN_SEL(R200_SEL_DDC3);
				break;
			default:
				DRM_ERROR("gpio not supported with hw i2c\n");
				ret = -EINVAL;
				goto done;
			}
			break;
		default:
			DRM_ERROR("unsupported asic\n");
			ret = -EINVAL;
			goto done;
			break;
		}
	}

	/* check for bus probe */
	p = &msgs[0];
	if ((num == 1) && (p->len == 0)) {
		WREG32(i2c_cntl_0, (RADEON_I2C_DONE |
				    RADEON_I2C_NACK |
				    RADEON_I2C_HALT |
				    RADEON_I2C_SOFT_RST));
		WREG32(i2c_data, (p->addr << 1) & 0xff);
		WREG32(i2c_data, 0);
		WREG32(i2c_cntl_1, ((1 << RADEON_I2C_DATA_COUNT_SHIFT) |
				    (1 << RADEON_I2C_ADDR_COUNT_SHIFT) |
				    RADEON_I2C_EN |
				    (48 << RADEON_I2C_TIME_LIMIT_SHIFT)));
		WREG32(i2c_cntl_0, reg);
		for (k = 0; k < 32; k++) {
			udelay(10);
			tmp = RREG32(i2c_cntl_0);
			if (tmp & RADEON_I2C_GO)
				continue;
			tmp = RREG32(i2c_cntl_0);
			if (tmp & RADEON_I2C_DONE)
				break;
			else {
				DRM_DEBUG("i2c write error 0x%08x\n", tmp);
				WREG32(i2c_cntl_0, tmp | RADEON_I2C_ABORT);
				ret = -EIO;
				goto done;
			}
		}
		goto done;
	}

	for (i = 0; i < num; i++) {
		p = &msgs[i];
		for (j = 0; j < p->len; j++) {
			if (p->flags & I2C_M_RD) {
				WREG32(i2c_cntl_0, (RADEON_I2C_DONE |
						    RADEON_I2C_NACK |
						    RADEON_I2C_HALT |
						    RADEON_I2C_SOFT_RST));
				WREG32(i2c_data, ((p->addr << 1) & 0xff) | 0x1);
				WREG32(i2c_cntl_1, ((1 << RADEON_I2C_DATA_COUNT_SHIFT) |
						    (1 << RADEON_I2C_ADDR_COUNT_SHIFT) |
						    RADEON_I2C_EN |
						    (48 << RADEON_I2C_TIME_LIMIT_SHIFT)));
				WREG32(i2c_cntl_0, reg | RADEON_I2C_RECEIVE);
				for (k = 0; k < 32; k++) {
					udelay(10);
					tmp = RREG32(i2c_cntl_0);
					if (tmp & RADEON_I2C_GO)
						continue;
					tmp = RREG32(i2c_cntl_0);
					if (tmp & RADEON_I2C_DONE)
						break;
					else {
						DRM_DEBUG("i2c read error 0x%08x\n", tmp);
						WREG32(i2c_cntl_0, tmp | RADEON_I2C_ABORT);
						ret = -EIO;
						goto done;
					}
				}
				p->buf[j] = RREG32(i2c_data) & 0xff;
			} else {
				WREG32(i2c_cntl_0, (RADEON_I2C_DONE |
						    RADEON_I2C_NACK |
						    RADEON_I2C_HALT |
						    RADEON_I2C_SOFT_RST));
				WREG32(i2c_data, (p->addr << 1) & 0xff);
				WREG32(i2c_data, p->buf[j]);
				WREG32(i2c_cntl_1, ((1 << RADEON_I2C_DATA_COUNT_SHIFT) |
						    (1 << RADEON_I2C_ADDR_COUNT_SHIFT) |
						    RADEON_I2C_EN |
						    (48 << RADEON_I2C_TIME_LIMIT_SHIFT)));
				WREG32(i2c_cntl_0, reg);
				for (k = 0; k < 32; k++) {
					udelay(10);
					tmp = RREG32(i2c_cntl_0);
					if (tmp & RADEON_I2C_GO)
						continue;
					tmp = RREG32(i2c_cntl_0);
					if (tmp & RADEON_I2C_DONE)
						break;
					else {
						DRM_DEBUG("i2c write error 0x%08x\n", tmp);
						WREG32(i2c_cntl_0, tmp | RADEON_I2C_ABORT);
						ret = -EIO;
						goto done;
					}
				}
			}
		}
	}

done:
	WREG32(i2c_cntl_0, 0);
	WREG32(i2c_cntl_1, 0);
	WREG32(i2c_cntl_0, (RADEON_I2C_DONE |
			    RADEON_I2C_NACK |
			    RADEON_I2C_HALT |
			    RADEON_I2C_SOFT_RST));

	if (rdev->is_atom_bios) {
		tmp = RREG32(RADEON_BIOS_6_SCRATCH);
		tmp &= ~ATOM_S6_HW_I2C_BUSY_STATE;
		WREG32(RADEON_BIOS_6_SCRATCH, tmp);
	}

	mutex_unlock(&rdev->pm.mutex);
	mutex_unlock(&rdev->dc_hw_i2c_mutex);

	return ret;
}
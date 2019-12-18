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
struct s2mps11_info {int ramp_delay16; int ramp_delay2; int ramp_delay34; int ramp_delay5; int ramp_delay7810; int ramp_delay9; } ;
struct regulator_dev {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  S2MPS11_BUCK1 137 
#define  S2MPS11_BUCK10 136 
 unsigned int S2MPS11_BUCK16_RAMP_SHIFT ; 
#define  S2MPS11_BUCK2 135 
 unsigned int S2MPS11_BUCK2_RAMP_EN_SHIFT ; 
 unsigned int S2MPS11_BUCK2_RAMP_SHIFT ; 
#define  S2MPS11_BUCK3 134 
 unsigned int S2MPS11_BUCK34_RAMP_SHIFT ; 
 unsigned int S2MPS11_BUCK3_RAMP_EN_SHIFT ; 
#define  S2MPS11_BUCK4 133 
 unsigned int S2MPS11_BUCK4_RAMP_EN_SHIFT ; 
#define  S2MPS11_BUCK5 132 
 unsigned int S2MPS11_BUCK5_RAMP_SHIFT ; 
#define  S2MPS11_BUCK6 131 
 unsigned int S2MPS11_BUCK6_RAMP_EN_SHIFT ; 
#define  S2MPS11_BUCK7 130 
 unsigned int S2MPS11_BUCK7810_RAMP_SHIFT ; 
#define  S2MPS11_BUCK8 129 
#define  S2MPS11_BUCK9 128 
 unsigned int S2MPS11_BUCK9_RAMP_SHIFT ; 
 unsigned int S2MPS11_REG_RAMP ; 
 unsigned int S2MPS11_REG_RAMP_BUCK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned int get_ramp_delay (int) ; 
 struct s2mps11_info* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,int,unsigned int) ; 

__attribute__((used)) static int s2mps11_set_ramp_delay(struct regulator_dev *rdev, int ramp_delay)
{
	struct s2mps11_info *s2mps11 = rdev_get_drvdata(rdev);
	unsigned int ramp_val, ramp_shift, ramp_reg = S2MPS11_REG_RAMP_BUCK;
	unsigned int ramp_enable = 1, enable_shift = 0;
	int rdev_id = rdev_get_id(rdev);
	int ret;

	switch (rdev_id) {
	case S2MPS11_BUCK1:
		if (ramp_delay > s2mps11->ramp_delay16)
			s2mps11->ramp_delay16 = ramp_delay;
		else
			ramp_delay = s2mps11->ramp_delay16;

		ramp_shift = S2MPS11_BUCK16_RAMP_SHIFT;
		break;
	case S2MPS11_BUCK2:
		enable_shift = S2MPS11_BUCK2_RAMP_EN_SHIFT;
		if (!ramp_delay) {
			ramp_enable = 0;
			break;
		}

		s2mps11->ramp_delay2 = ramp_delay;
		ramp_shift = S2MPS11_BUCK2_RAMP_SHIFT;
		ramp_reg = S2MPS11_REG_RAMP;
		break;
	case S2MPS11_BUCK3:
		enable_shift = S2MPS11_BUCK3_RAMP_EN_SHIFT;
		if (!ramp_delay) {
			ramp_enable = 0;
			break;
		}

		if (ramp_delay > s2mps11->ramp_delay34)
			s2mps11->ramp_delay34 = ramp_delay;
		else
			ramp_delay = s2mps11->ramp_delay34;

		ramp_shift = S2MPS11_BUCK34_RAMP_SHIFT;
		ramp_reg = S2MPS11_REG_RAMP;
		break;
	case S2MPS11_BUCK4:
		enable_shift = S2MPS11_BUCK4_RAMP_EN_SHIFT;
		if (!ramp_delay) {
			ramp_enable = 0;
			break;
		}

		if (ramp_delay > s2mps11->ramp_delay34)
			s2mps11->ramp_delay34 = ramp_delay;
		else
			ramp_delay = s2mps11->ramp_delay34;

		ramp_shift = S2MPS11_BUCK34_RAMP_SHIFT;
		ramp_reg = S2MPS11_REG_RAMP;
		break;
	case S2MPS11_BUCK5:
		s2mps11->ramp_delay5 = ramp_delay;
		ramp_shift = S2MPS11_BUCK5_RAMP_SHIFT;
		break;
	case S2MPS11_BUCK6:
		enable_shift = S2MPS11_BUCK6_RAMP_EN_SHIFT;
		if (!ramp_delay) {
			ramp_enable = 0;
			break;
		}

		if (ramp_delay > s2mps11->ramp_delay16)
			s2mps11->ramp_delay16 = ramp_delay;
		else
			ramp_delay = s2mps11->ramp_delay16;

		ramp_shift = S2MPS11_BUCK16_RAMP_SHIFT;
		break;
	case S2MPS11_BUCK7:
	case S2MPS11_BUCK8:
	case S2MPS11_BUCK10:
		if (ramp_delay > s2mps11->ramp_delay7810)
			s2mps11->ramp_delay7810 = ramp_delay;
		else
			ramp_delay = s2mps11->ramp_delay7810;

		ramp_shift = S2MPS11_BUCK7810_RAMP_SHIFT;
		break;
	case S2MPS11_BUCK9:
		s2mps11->ramp_delay9 = ramp_delay;
		ramp_shift = S2MPS11_BUCK9_RAMP_SHIFT;
		break;
	default:
		return 0;
	}

	if (!ramp_enable)
		goto ramp_disable;

	/* Ramp delay can be enabled/disabled only for buck[2346] */
	if ((rdev_id >= S2MPS11_BUCK2 && rdev_id <= S2MPS11_BUCK4) ||
	    rdev_id == S2MPS11_BUCK6)  {
		ret = regmap_update_bits(rdev->regmap, S2MPS11_REG_RAMP,
					 1 << enable_shift, 1 << enable_shift);
		if (ret) {
			dev_err(&rdev->dev, "failed to enable ramp rate\n");
			return ret;
		}
	}

	ramp_val = get_ramp_delay(ramp_delay);

	return regmap_update_bits(rdev->regmap, ramp_reg, 0x3 << ramp_shift,
				  ramp_val << ramp_shift);

ramp_disable:
	return regmap_update_bits(rdev->regmap, S2MPS11_REG_RAMP,
				  1 << enable_shift, 0);
}
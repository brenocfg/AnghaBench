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
struct regulator_dev {TYPE_1__* desc; } ;
struct pfuze_chip {int chip_id; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {scalar_t__ vsel_reg; } ;

/* Variables and functions */
 int EACCES ; 
#define  PFUZE100 131 
 int PFUZE100_SWBST ; 
#define  PFUZE200 130 
 int PFUZE200_SWBST ; 
#define  PFUZE3000 129 
 int PFUZE3000_SWBST ; 
#define  PFUZE3001 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct pfuze_chip* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,unsigned int) ; 

__attribute__((used)) static int pfuze100_set_ramp_delay(struct regulator_dev *rdev, int ramp_delay)
{
	struct pfuze_chip *pfuze100 = rdev_get_drvdata(rdev);
	int id = rdev_get_id(rdev);
	bool reg_has_ramp_delay;
	unsigned int ramp_bits;
	int ret;

	switch (pfuze100->chip_id) {
	case PFUZE3001:
		/* no dynamic voltage scaling for PF3001 */
		reg_has_ramp_delay = false;
		break;
	case PFUZE3000:
		reg_has_ramp_delay = (id < PFUZE3000_SWBST);
		break;
	case PFUZE200:
		reg_has_ramp_delay = (id < PFUZE200_SWBST);
		break;
	case PFUZE100:
	default:
		reg_has_ramp_delay = (id < PFUZE100_SWBST);
		break;
	}

	if (reg_has_ramp_delay) {
		ramp_delay = 12500 / ramp_delay;
		ramp_bits = (ramp_delay >> 1) - (ramp_delay >> 3);
		ret = regmap_update_bits(pfuze100->regmap,
					 rdev->desc->vsel_reg + 4,
					 0xc0, ramp_bits << 6);
		if (ret < 0)
			dev_err(pfuze100->dev, "ramp failed, err %d\n", ret);
	} else {
		ret = -EACCES;
	}

	return ret;
}
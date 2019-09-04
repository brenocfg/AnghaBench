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
struct iio_trigger {int dummy; } ;
struct iio_dev {int dummy; } ;
struct hts221_hw {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HTS221_REG_DRDY_EN_ADDR ; 
 int /*<<< orphan*/  HTS221_REG_DRDY_EN_MASK ; 
 struct hts221_hw* iio_priv (struct iio_dev*) ; 
 struct iio_dev* iio_trigger_get_drvdata (struct iio_trigger*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hts221_trig_set_state(struct iio_trigger *trig, bool state)
{
	struct iio_dev *iio_dev = iio_trigger_get_drvdata(trig);
	struct hts221_hw *hw = iio_priv(iio_dev);

	return regmap_update_bits(hw->regmap, HTS221_REG_DRDY_EN_ADDR,
				  HTS221_REG_DRDY_EN_MASK,
				  FIELD_PREP(HTS221_REG_DRDY_EN_MASK, state));
}
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
struct meson_msr_id {unsigned int id; struct meson_msr* priv; } ;
struct meson_msr {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST_ULL (unsigned int,unsigned int) ; 
 int EINVAL ; 
 int FIELD_PREP (int,unsigned int) ; 
 unsigned int MSR_BUSY ; 
 int /*<<< orphan*/  MSR_CLK_REG0 ; 
 int /*<<< orphan*/  MSR_CLK_REG2 ; 
 int MSR_CLK_SRC ; 
 int MSR_DURATION ; 
 int MSR_ENABLE ; 
 int MSR_RUN ; 
 unsigned int MSR_VAL_MASK ; 
 int /*<<< orphan*/  measure_lock ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_measure_id(struct meson_msr_id *clk_msr_id,
			       unsigned int duration)
{
	struct meson_msr *priv = clk_msr_id->priv;
	unsigned int val;
	int ret;

	ret = mutex_lock_interruptible(&measure_lock);
	if (ret)
		return ret;

	regmap_write(priv->regmap, MSR_CLK_REG0, 0);

	/* Set measurement duration */
	regmap_update_bits(priv->regmap, MSR_CLK_REG0, MSR_DURATION,
			   FIELD_PREP(MSR_DURATION, duration - 1));

	/* Set ID */
	regmap_update_bits(priv->regmap, MSR_CLK_REG0, MSR_CLK_SRC,
			   FIELD_PREP(MSR_CLK_SRC, clk_msr_id->id));

	/* Enable & Start */
	regmap_update_bits(priv->regmap, MSR_CLK_REG0,
			   MSR_RUN | MSR_ENABLE,
			   MSR_RUN | MSR_ENABLE);

	ret = regmap_read_poll_timeout(priv->regmap, MSR_CLK_REG0,
				       val, !(val & MSR_BUSY), 10, 10000);
	if (ret) {
		mutex_unlock(&measure_lock);
		return ret;
	}

	/* Disable */
	regmap_update_bits(priv->regmap, MSR_CLK_REG0, MSR_ENABLE, 0);

	/* Get the value in multiple of gate time counts */
	regmap_read(priv->regmap, MSR_CLK_REG2, &val);

	mutex_unlock(&measure_lock);

	if (val >= MSR_VAL_MASK)
		return -EINVAL;

	return DIV_ROUND_CLOSEST_ULL((val & MSR_VAL_MASK) * 1000000ULL,
				     duration);
}
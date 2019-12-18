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
typedef  int u32 ;
struct ti_iodelay_reg_values {int cdpe; int fdpe; } ;
struct ti_iodelay_reg_data {int signature_mask; int signature_value; int binary_data_coarse_mask; int binary_data_fine_mask; int lock_mask; int unlock_val; } ;
struct ti_iodelay_device {int /*<<< orphan*/  regmap; struct device* dev; struct ti_iodelay_reg_values reg_init_conf_values; struct ti_iodelay_reg_data* reg_data; } ;
struct ti_iodelay_cfg {int g_delay; int a_delay; int /*<<< orphan*/  offset; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int __ffs (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ti_iodelay_pinconf_set(struct ti_iodelay_device *iod,
				  struct ti_iodelay_cfg *cfg)
{
	const struct ti_iodelay_reg_data *reg = iod->reg_data;
	struct ti_iodelay_reg_values *ival = &iod->reg_init_conf_values;
	struct device *dev = iod->dev;
	u32 g_delay_coarse, g_delay_fine;
	u32 a_delay_coarse, a_delay_fine;
	u32 c_elements, f_elements;
	u32 total_delay;
	u32 reg_mask, reg_val, tmp_val;
	int r;

	/* NOTE: Truncation is expected in all division below */
	g_delay_coarse = cfg->g_delay / 920;
	g_delay_fine = ((cfg->g_delay % 920) * 10) / 60;

	a_delay_coarse = cfg->a_delay / ival->cdpe;
	a_delay_fine = ((cfg->a_delay % ival->cdpe) * 10) / ival->fdpe;

	c_elements = g_delay_coarse + a_delay_coarse;
	f_elements = (g_delay_fine + a_delay_fine) / 10;

	if (f_elements > 22) {
		total_delay = c_elements * ival->cdpe + f_elements * ival->fdpe;
		c_elements = total_delay / ival->cdpe;
		f_elements = (total_delay % ival->cdpe) / ival->fdpe;
	}

	reg_mask = reg->signature_mask;
	reg_val = reg->signature_value << __ffs(reg->signature_mask);

	reg_mask |= reg->binary_data_coarse_mask;
	tmp_val = c_elements << __ffs(reg->binary_data_coarse_mask);
	if (tmp_val & ~reg->binary_data_coarse_mask) {
		dev_err(dev, "Masking overflow of coarse elements %08x\n",
			tmp_val);
		tmp_val &= reg->binary_data_coarse_mask;
	}
	reg_val |= tmp_val;

	reg_mask |= reg->binary_data_fine_mask;
	tmp_val = f_elements << __ffs(reg->binary_data_fine_mask);
	if (tmp_val & ~reg->binary_data_fine_mask) {
		dev_err(dev, "Masking overflow of fine elements %08x\n",
			tmp_val);
		tmp_val &= reg->binary_data_fine_mask;
	}
	reg_val |= tmp_val;

	/*
	 * NOTE: we leave the iodelay values unlocked - this is to work around
	 * situations such as those found with mmc mode change.
	 * However, this leaves open any unwarranted changes to padconf register
	 * impacting iodelay configuration. Use with care!
	 */
	reg_mask |= reg->lock_mask;
	reg_val |= reg->unlock_val << __ffs(reg->lock_mask);
	r = regmap_update_bits(iod->regmap, cfg->offset, reg_mask, reg_val);

	dev_dbg(dev, "Set reg 0x%x Delay(a: %d g: %d), Elements(C=%d F=%d)0x%x\n",
		cfg->offset, cfg->a_delay, cfg->g_delay, c_elements,
		f_elements, reg_val);

	return r;
}
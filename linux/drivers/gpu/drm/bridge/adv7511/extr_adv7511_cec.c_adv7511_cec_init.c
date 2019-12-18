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
struct device {int dummy; } ;
struct adv7511 {scalar_t__ type; int cec_clk_freq; int /*<<< orphan*/  regmap; int /*<<< orphan*/ * cec_adap; int /*<<< orphan*/  regmap_cec; } ;

/* Variables and functions */
 int ADV7511_CEC_CTRL_POWER_DOWN ; 
 int /*<<< orphan*/  ADV7511_MAX_ADDRS ; 
 scalar_t__ ADV7511_REG_CEC_CLK_DIV ; 
 scalar_t__ ADV7511_REG_CEC_CTRL ; 
 scalar_t__ ADV7511_REG_CEC_RX_BUFFERS ; 
 scalar_t__ ADV7511_REG_CEC_SOFT_RESET ; 
 scalar_t__ ADV7533 ; 
 unsigned int ADV7533_REG_CEC_OFFSET ; 
 int /*<<< orphan*/  CEC_CAP_DEFAULTS ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adv7511_cec_adap_ops ; 
 int adv7511_cec_parse_dt (struct device*,struct adv7511*) ; 
 int /*<<< orphan*/ * cec_allocate_adapter (int /*<<< orphan*/ *,struct adv7511*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_delete_adapter (int /*<<< orphan*/ *) ; 
 int cec_register_adapter (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 

int adv7511_cec_init(struct device *dev, struct adv7511 *adv7511)
{
	unsigned int offset = adv7511->type == ADV7533 ?
						ADV7533_REG_CEC_OFFSET : 0;
	int ret = adv7511_cec_parse_dt(dev, adv7511);

	if (ret)
		goto err_cec_parse_dt;

	adv7511->cec_adap = cec_allocate_adapter(&adv7511_cec_adap_ops,
		adv7511, dev_name(dev), CEC_CAP_DEFAULTS, ADV7511_MAX_ADDRS);
	if (IS_ERR(adv7511->cec_adap)) {
		ret = PTR_ERR(adv7511->cec_adap);
		goto err_cec_alloc;
	}

	regmap_write(adv7511->regmap, ADV7511_REG_CEC_CTRL + offset, 0);
	/* cec soft reset */
	regmap_write(adv7511->regmap_cec,
		     ADV7511_REG_CEC_SOFT_RESET + offset, 0x01);
	regmap_write(adv7511->regmap_cec,
		     ADV7511_REG_CEC_SOFT_RESET + offset, 0x00);

	/* legacy mode */
	regmap_write(adv7511->regmap_cec,
		     ADV7511_REG_CEC_RX_BUFFERS + offset, 0x00);

	regmap_write(adv7511->regmap_cec,
		     ADV7511_REG_CEC_CLK_DIV + offset,
		     ((adv7511->cec_clk_freq / 750000) - 1) << 2);

	ret = cec_register_adapter(adv7511->cec_adap, dev);
	if (ret)
		goto err_cec_register;
	return 0;

err_cec_register:
	cec_delete_adapter(adv7511->cec_adap);
	adv7511->cec_adap = NULL;
err_cec_alloc:
	dev_info(dev, "Initializing CEC failed with error %d, disabling CEC\n",
		 ret);
err_cec_parse_dt:
	regmap_write(adv7511->regmap, ADV7511_REG_CEC_CTRL + offset,
		     ADV7511_CEC_CTRL_POWER_DOWN);
	return ret == -EPROBE_DEFER ? ret : 0;
}
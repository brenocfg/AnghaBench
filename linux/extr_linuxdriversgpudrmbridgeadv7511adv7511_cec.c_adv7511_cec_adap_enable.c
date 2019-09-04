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
struct cec_adapter {int dummy; } ;
struct adv7511 {scalar_t__ type; int cec_enabled_adap; scalar_t__ cec_valid_addrs; int /*<<< orphan*/  regmap_cec; int /*<<< orphan*/  regmap; int /*<<< orphan*/ * i2c_cec; } ;

/* Variables and functions */
 int ADV7511_INT1_CEC_MASK ; 
 scalar_t__ ADV7511_REG_CEC_CLK_DIV ; 
 scalar_t__ ADV7511_REG_CEC_LOG_ADDR_MASK ; 
 scalar_t__ ADV7511_REG_CEC_RX_BUFFERS ; 
 scalar_t__ ADV7511_REG_CEC_TX_ENABLE ; 
 scalar_t__ ADV7511_REG_INT_ENABLE (int) ; 
 scalar_t__ ADV7533 ; 
 unsigned int ADV7533_REG_CEC_OFFSET ; 
 int EIO ; 
 struct adv7511* cec_get_drvdata (struct cec_adapter*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int adv7511_cec_adap_enable(struct cec_adapter *adap, bool enable)
{
	struct adv7511 *adv7511 = cec_get_drvdata(adap);
	unsigned int offset = adv7511->type == ADV7533 ?
					ADV7533_REG_CEC_OFFSET : 0;

	if (adv7511->i2c_cec == NULL)
		return -EIO;

	if (!adv7511->cec_enabled_adap && enable) {
		/* power up cec section */
		regmap_update_bits(adv7511->regmap_cec,
				   ADV7511_REG_CEC_CLK_DIV + offset,
				   0x03, 0x01);
		/* legacy mode and clear all rx buffers */
		regmap_write(adv7511->regmap_cec,
			     ADV7511_REG_CEC_RX_BUFFERS + offset, 0x07);
		regmap_write(adv7511->regmap_cec,
			     ADV7511_REG_CEC_RX_BUFFERS + offset, 0);
		/* initially disable tx */
		regmap_update_bits(adv7511->regmap_cec,
				   ADV7511_REG_CEC_TX_ENABLE + offset, 1, 0);
		/* enabled irqs: */
		/* tx: ready */
		/* tx: arbitration lost */
		/* tx: retry timeout */
		/* rx: ready 1 */
		regmap_update_bits(adv7511->regmap,
				   ADV7511_REG_INT_ENABLE(1), 0x3f,
				   ADV7511_INT1_CEC_MASK);
	} else if (adv7511->cec_enabled_adap && !enable) {
		regmap_update_bits(adv7511->regmap,
				   ADV7511_REG_INT_ENABLE(1), 0x3f, 0);
		/* disable address mask 1-3 */
		regmap_update_bits(adv7511->regmap_cec,
				   ADV7511_REG_CEC_LOG_ADDR_MASK + offset,
				   0x70, 0x00);
		/* power down cec section */
		regmap_update_bits(adv7511->regmap_cec,
				   ADV7511_REG_CEC_CLK_DIV + offset,
				   0x03, 0x00);
		adv7511->cec_valid_addrs = 0;
	}
	adv7511->cec_enabled_adap = enable;
	return 0;
}
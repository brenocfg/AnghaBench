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
typedef  unsigned int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct cec_msg {unsigned int len; int* msg; } ;
struct cec_adapter {int dummy; } ;
struct adv7511 {scalar_t__ type; int /*<<< orphan*/  regmap_cec; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ ADV7511_REG_CEC_TX_ENABLE ; 
 scalar_t__ ADV7511_REG_CEC_TX_FRAME_HDR ; 
 scalar_t__ ADV7511_REG_CEC_TX_FRAME_LEN ; 
 scalar_t__ ADV7511_REG_CEC_TX_RETRY ; 
 scalar_t__ ADV7511_REG_INT (int) ; 
 scalar_t__ ADV7533 ; 
 unsigned int ADV7533_REG_CEC_OFFSET ; 
 struct adv7511* cec_get_drvdata (struct cec_adapter*) ; 
 int max (int,unsigned int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int adv7511_cec_adap_transmit(struct cec_adapter *adap, u8 attempts,
				     u32 signal_free_time, struct cec_msg *msg)
{
	struct adv7511 *adv7511 = cec_get_drvdata(adap);
	unsigned int offset = adv7511->type == ADV7533 ?
					ADV7533_REG_CEC_OFFSET : 0;
	u8 len = msg->len;
	unsigned int i;

	/*
	 * The number of retries is the number of attempts - 1, but retry
	 * at least once. It's not clear if a value of 0 is allowed, so
	 * let's do at least one retry.
	 */
	regmap_update_bits(adv7511->regmap_cec,
			   ADV7511_REG_CEC_TX_RETRY + offset,
			   0x70, max(1, attempts - 1) << 4);

	/* blocking, clear cec tx irq status */
	regmap_update_bits(adv7511->regmap, ADV7511_REG_INT(1), 0x38, 0x38);

	/* write data */
	for (i = 0; i < len; i++)
		regmap_write(adv7511->regmap_cec,
			     i + ADV7511_REG_CEC_TX_FRAME_HDR + offset,
			     msg->msg[i]);

	/* set length (data + header) */
	regmap_write(adv7511->regmap_cec,
		     ADV7511_REG_CEC_TX_FRAME_LEN + offset, len);
	/* start transmit, enable tx */
	regmap_write(adv7511->regmap_cec,
		     ADV7511_REG_CEC_TX_ENABLE + offset, 0x01);
	return 0;
}
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
typedef  size_t u8 ;
typedef  unsigned int u32 ;
struct cec_msg {unsigned int len; unsigned int* msg; } ;
struct adv7511 {scalar_t__ type; int /*<<< orphan*/  cec_adap; int /*<<< orphan*/  regmap_cec; } ;

/* Variables and functions */
 unsigned int ADV7511_INT1_CEC_RX_READY1 ; 
 unsigned int ADV7511_INT1_CEC_TX_ARBIT_LOST ; 
 unsigned int ADV7511_INT1_CEC_TX_READY ; 
 unsigned int ADV7511_INT1_CEC_TX_RETRY_TIMEOUT ; 
 scalar_t__ ADV7511_REG_CEC_RX_BUFFERS ; 
 scalar_t__ ADV7511_REG_CEC_RX_FRAME_HDR ; 
 scalar_t__ ADV7511_REG_CEC_RX_FRAME_LEN ; 
 scalar_t__ ADV7533 ; 
 unsigned int ADV7533_REG_CEC_OFFSET ; 
 int /*<<< orphan*/  adv_cec_tx_raw_status (struct adv7511*,unsigned int) ; 
 int /*<<< orphan*/  cec_received_msg (int /*<<< orphan*/ ,struct cec_msg*) ; 
 scalar_t__ regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 

void adv7511_cec_irq_process(struct adv7511 *adv7511, unsigned int irq1)
{
	unsigned int offset = adv7511->type == ADV7533 ?
					ADV7533_REG_CEC_OFFSET : 0;
	const u32 irq_tx_mask = ADV7511_INT1_CEC_TX_READY |
				ADV7511_INT1_CEC_TX_ARBIT_LOST |
				ADV7511_INT1_CEC_TX_RETRY_TIMEOUT;
	struct cec_msg msg = {};
	unsigned int len;
	unsigned int val;
	u8 i;

	if (irq1 & irq_tx_mask)
		adv_cec_tx_raw_status(adv7511, irq1);

	if (!(irq1 & ADV7511_INT1_CEC_RX_READY1))
		return;

	if (regmap_read(adv7511->regmap_cec,
			ADV7511_REG_CEC_RX_FRAME_LEN + offset, &len))
		return;

	msg.len = len & 0x1f;

	if (msg.len > 16)
		msg.len = 16;

	if (!msg.len)
		return;

	for (i = 0; i < msg.len; i++) {
		regmap_read(adv7511->regmap_cec,
			    i + ADV7511_REG_CEC_RX_FRAME_HDR + offset, &val);
		msg.msg[i] = val;
	}

	/* toggle to re-enable rx 1 */
	regmap_write(adv7511->regmap_cec,
		     ADV7511_REG_CEC_RX_BUFFERS + offset, 1);
	regmap_write(adv7511->regmap_cec,
		     ADV7511_REG_CEC_RX_BUFFERS + offset, 0);
	cec_received_msg(adv7511->cec_adap, &msg);
}
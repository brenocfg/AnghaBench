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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct cec_msg {int len; int /*<<< orphan*/ * msg; } ;
struct stm32_cec {scalar_t__ tx_cnt; struct cec_msg tx_msg; int /*<<< orphan*/  regmap; } ;
struct cec_adapter {struct stm32_cec* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_CR ; 
 int /*<<< orphan*/  CEC_TXDR ; 
 int /*<<< orphan*/  TXEOM ; 
 int /*<<< orphan*/  TXSOM ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_cec_adap_transmit(struct cec_adapter *adap, u8 attempts,
				   u32 signal_free_time, struct cec_msg *msg)
{
	struct stm32_cec *cec = adap->priv;

	/* Copy message */
	cec->tx_msg = *msg;
	cec->tx_cnt = 0;

	/*
	 * If the CEC message consists of only one byte,
	 * TXEOM must be set before of TXSOM.
	 */
	if (cec->tx_msg.len == 1)
		regmap_update_bits(cec->regmap, CEC_CR, TXEOM, TXEOM);

	/* TXSOM is set to command transmission of the first byte */
	regmap_update_bits(cec->regmap, CEC_CR, TXSOM, TXSOM);

	/* Write the header (first byte of message) */
	regmap_write(cec->regmap, CEC_TXDR, cec->tx_msg.msg[0]);
	cec->tx_cnt++;

	return 0;
}
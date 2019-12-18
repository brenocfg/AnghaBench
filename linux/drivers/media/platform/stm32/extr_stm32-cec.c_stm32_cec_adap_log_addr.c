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
typedef  int u8 ;
typedef  int u32 ;
struct stm32_cec {int /*<<< orphan*/  regmap; } ;
struct cec_adapter {struct stm32_cec* priv; } ;

/* Variables and functions */
 int CECEN ; 
 int /*<<< orphan*/  CEC_CFGR ; 
 int /*<<< orphan*/  CEC_CR ; 
 int CEC_LOG_ADDR_INVALID ; 
 int CEC_XFER_TIMEOUT_MS ; 
 int OAR ; 
 int TXSOM ; 
 int /*<<< orphan*/  regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int stm32_cec_adap_log_addr(struct cec_adapter *adap, u8 logical_addr)
{
	struct stm32_cec *cec = adap->priv;
	u32 oar = (1 << logical_addr) << 16;
	u32 val;

	/* Poll every 100µs the register CEC_CR to wait end of transmission */
	regmap_read_poll_timeout(cec->regmap, CEC_CR, val, !(val & TXSOM),
				 100, CEC_XFER_TIMEOUT_MS * 1000);
	regmap_update_bits(cec->regmap, CEC_CR, CECEN, 0);

	if (logical_addr == CEC_LOG_ADDR_INVALID)
		regmap_update_bits(cec->regmap, CEC_CFGR, OAR, 0);
	else
		regmap_update_bits(cec->regmap, CEC_CFGR, oar, oar);

	regmap_update_bits(cec->regmap, CEC_CR, CECEN, CECEN);

	return 0;
}
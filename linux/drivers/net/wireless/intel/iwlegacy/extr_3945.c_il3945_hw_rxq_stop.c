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
struct il_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FH39_RCSR_CONFIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FH39_RSSR_CHNL0_RX_STATUS_CHNL_IDLE ; 
 int /*<<< orphan*/  FH39_RSSR_STATUS ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 int _il_poll_bit (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _il_wr (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
il3945_hw_rxq_stop(struct il_priv *il)
{
	int ret;

	_il_wr(il, FH39_RCSR_CONFIG(0), 0);
	ret = _il_poll_bit(il, FH39_RSSR_STATUS,
			   FH39_RSSR_CHNL0_RX_STATUS_CHNL_IDLE,
			   FH39_RSSR_CHNL0_RX_STATUS_CHNL_IDLE,
			   1000);
	if (ret < 0)
		IL_ERR("Can't stop Rx DMA.\n");

	return 0;
}
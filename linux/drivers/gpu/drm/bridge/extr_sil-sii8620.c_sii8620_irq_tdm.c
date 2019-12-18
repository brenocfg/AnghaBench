#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  r_size; scalar_t__ rx_ack; } ;
struct sii8620 {TYPE_1__ burst; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_MHL_PLL_CTL2_CLKDETECT_EN ; 
 int /*<<< orphan*/  CM_ECBUS_S ; 
 int MSK_TDM_SYNCHRONIZED ; 
 int /*<<< orphan*/  REG_MHL_PLL_CTL2 ; 
 int /*<<< orphan*/  REG_TRXINTH ; 
 int /*<<< orphan*/  REG_TRXSTA2 ; 
 int /*<<< orphan*/  SII8620_BURST_BUF_LEN ; 
 int VAL_TDM_SYNCHRONIZED ; 
 int /*<<< orphan*/  sii8620_burst_tx_rbuf_info (struct sii8620*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sii8620_got_xdevcap ; 
 int /*<<< orphan*/  sii8620_mt_read_devcap (struct sii8620*,int) ; 
 int /*<<< orphan*/  sii8620_mt_set_cont (struct sii8620*,int /*<<< orphan*/ ) ; 
 int sii8620_readb (struct sii8620*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sii8620_write (struct sii8620*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sii8620_write_seq_static (struct sii8620*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sii8620_irq_tdm(struct sii8620 *ctx)
{
	u8 stat = sii8620_readb(ctx, REG_TRXINTH);
	u8 tdm = sii8620_readb(ctx, REG_TRXSTA2);

	if ((tdm & MSK_TDM_SYNCHRONIZED) == VAL_TDM_SYNCHRONIZED) {
		ctx->mode = CM_ECBUS_S;
		ctx->burst.rx_ack = 0;
		ctx->burst.r_size = SII8620_BURST_BUF_LEN;
		sii8620_burst_tx_rbuf_info(ctx, SII8620_BURST_BUF_LEN);
		sii8620_mt_read_devcap(ctx, true);
		sii8620_mt_set_cont(ctx, sii8620_got_xdevcap);
	} else {
		sii8620_write_seq_static(ctx,
			REG_MHL_PLL_CTL2, 0,
			REG_MHL_PLL_CTL2, BIT_MHL_PLL_CTL2_CLKDETECT_EN
		);
	}

	sii8620_write(ctx, REG_TRXINTH, stat);
}
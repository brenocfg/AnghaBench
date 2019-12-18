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
struct sii9234 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_RX_TMDS_CH_EN_REG ; 
 int /*<<< orphan*/  HDMI_RX_TMDS_CLK_EN_REG ; 
 int /*<<< orphan*/  TPI_DPD_REG ; 
 int /*<<< orphan*/  hdmi_writeb (struct sii9234*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mhl_tx_writeb (struct sii9234*,int,int) ; 
 int sii9234_clear_error (struct sii9234*) ; 
 int /*<<< orphan*/  tpi_writeb (struct sii9234*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sii9234_power_init(struct sii9234 *ctx)
{
	/* Force the SiI9234 into the D0 state. */
	tpi_writeb(ctx, TPI_DPD_REG, 0x3F);
	/* Enable TxPLL Clock */
	hdmi_writeb(ctx, HDMI_RX_TMDS_CLK_EN_REG, 0x01);
	/* Enable Tx Clock Path & Equalizer */
	hdmi_writeb(ctx, HDMI_RX_TMDS_CH_EN_REG, 0x15);
	/* Power Up TMDS */
	mhl_tx_writeb(ctx, 0x08, 0x35);
	return sii9234_clear_error(ctx);
}
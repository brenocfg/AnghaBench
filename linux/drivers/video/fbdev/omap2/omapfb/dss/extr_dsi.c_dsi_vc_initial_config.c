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
typedef  int /*<<< orphan*/  u32 ;
struct platform_device {int dummy; } ;
struct dsi_data {TYPE_1__* vc; } ;
struct TYPE_2__ {int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_VC_CTRL (int) ; 
 int /*<<< orphan*/  DSI_VC_SOURCE_L4 ; 
 int /*<<< orphan*/  DSSDBG (char*,int) ; 
 int /*<<< orphan*/  DSSERR (char*,int) ; 
 int /*<<< orphan*/  FEAT_DSI_VC_OCP_WIDTH ; 
 scalar_t__ FLD_GET (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_read_reg (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_write_reg (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dss_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_vc_initial_config(struct platform_device *dsidev, int channel)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);
	u32 r;

	DSSDBG("Initial config of virtual channel %d", channel);

	r = dsi_read_reg(dsidev, DSI_VC_CTRL(channel));

	if (FLD_GET(r, 15, 15)) /* VC_BUSY */
		DSSERR("VC(%d) busy when trying to configure it!\n",
				channel);

	r = FLD_MOD(r, 0, 1, 1); /* SOURCE, 0 = L4 */
	r = FLD_MOD(r, 0, 2, 2); /* BTA_SHORT_EN  */
	r = FLD_MOD(r, 0, 3, 3); /* BTA_LONG_EN */
	r = FLD_MOD(r, 0, 4, 4); /* MODE, 0 = command */
	r = FLD_MOD(r, 1, 7, 7); /* CS_TX_EN */
	r = FLD_MOD(r, 1, 8, 8); /* ECC_TX_EN */
	r = FLD_MOD(r, 0, 9, 9); /* MODE_SPEED, high speed on/off */
	if (dss_has_feature(FEAT_DSI_VC_OCP_WIDTH))
		r = FLD_MOD(r, 3, 11, 10);	/* OCP_WIDTH = 32 bit */

	r = FLD_MOD(r, 4, 29, 27); /* DMA_RX_REQ_NB = no dma */
	r = FLD_MOD(r, 4, 23, 21); /* DMA_TX_REQ_NB = no dma */

	dsi_write_reg(dsidev, DSI_VC_CTRL(channel), r);

	dsi->vc[channel].source = DSI_VC_SOURCE_L4;
}
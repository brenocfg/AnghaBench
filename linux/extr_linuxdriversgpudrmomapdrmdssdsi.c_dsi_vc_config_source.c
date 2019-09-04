#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dsi_data {TYPE_2__* vc; TYPE_1__* data; } ;
typedef  enum dsi_vc_source { ____Placeholder_dsi_vc_source } dsi_vc_source ;
struct TYPE_4__ {int source; } ;
struct TYPE_3__ {int quirks; } ;

/* Variables and functions */
 int DSI_QUIRK_DCS_CMD_CONFIG_VC ; 
 int /*<<< orphan*/  DSI_VC_CTRL (int) ; 
 int DSI_VC_SOURCE_VP ; 
 int /*<<< orphan*/  DSSDBG (char*,int) ; 
 int /*<<< orphan*/  DSSERR (char*,int) ; 
 int EIO ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dsi_data*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  dsi_sync_vc (struct dsi_data*,int) ; 
 int /*<<< orphan*/  dsi_vc_enable (struct dsi_data*,int,int) ; 
 int /*<<< orphan*/  wait_for_bit_change (struct dsi_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsi_vc_config_source(struct dsi_data *dsi, int channel,
				enum dsi_vc_source source)
{
	if (dsi->vc[channel].source == source)
		return 0;

	DSSDBG("Source config of virtual channel %d", channel);

	dsi_sync_vc(dsi, channel);

	dsi_vc_enable(dsi, channel, 0);

	/* VC_BUSY */
	if (!wait_for_bit_change(dsi, DSI_VC_CTRL(channel), 15, 0)) {
		DSSERR("vc(%d) busy when trying to config for VP\n", channel);
		return -EIO;
	}

	/* SOURCE, 0 = L4, 1 = video port */
	REG_FLD_MOD(dsi, DSI_VC_CTRL(channel), source, 1, 1);

	/* DCS_CMD_ENABLE */
	if (dsi->data->quirks & DSI_QUIRK_DCS_CMD_CONFIG_VC) {
		bool enable = source == DSI_VC_SOURCE_VP;
		REG_FLD_MOD(dsi, DSI_VC_CTRL(channel), enable, 30, 30);
	}

	dsi_vc_enable(dsi, channel, 1);

	dsi->vc[channel].source = source;

	return 0;
}
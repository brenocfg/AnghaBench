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
typedef  int u32 ;
typedef  int u16 ;
struct platform_device {int dummy; } ;
struct dsi_data {TYPE_1__* vc; scalar_t__ debug_write; } ;
struct TYPE_2__ {int vc_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_VC_CTRL (int) ; 
 int /*<<< orphan*/  DSI_VC_SHORT_PACKET_HEADER (int) ; 
 int /*<<< orphan*/  DSI_VC_SOURCE_L4 ; 
 int /*<<< orphan*/  DSSDBG (char*,int,int,int,int) ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EINVAL ; 
 scalar_t__ FLD_GET (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dsi_bus_is_locked (struct platform_device*) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_read_reg (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_vc_config_source (struct platform_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_write_reg (struct platform_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dsi_vc_send_short(struct platform_device *dsidev, int channel,
		u8 data_type, u16 data, u8 ecc)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);
	u32 r;
	u8 data_id;

	WARN_ON(!dsi_bus_is_locked(dsidev));

	if (dsi->debug_write)
		DSSDBG("dsi_vc_send_short(ch%d, dt %#x, b1 %#x, b2 %#x)\n",
				channel,
				data_type, data & 0xff, (data >> 8) & 0xff);

	dsi_vc_config_source(dsidev, channel, DSI_VC_SOURCE_L4);

	if (FLD_GET(dsi_read_reg(dsidev, DSI_VC_CTRL(channel)), 16, 16)) {
		DSSERR("ERROR FIFO FULL, aborting transfer\n");
		return -EINVAL;
	}

	data_id = data_type | dsi->vc[channel].vc_id << 6;

	r = (data_id << 0) | (data << 8) | (ecc << 24);

	dsi_write_reg(dsidev, DSI_VC_SHORT_PACKET_HEADER(channel), r);

	return 0;
}
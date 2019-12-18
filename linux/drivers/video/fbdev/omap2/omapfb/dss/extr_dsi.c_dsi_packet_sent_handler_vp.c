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
typedef  int /*<<< orphan*/  u32 ;
struct dsi_packet_sent_handler_data {int /*<<< orphan*/  completion; int /*<<< orphan*/  dsidev; } ;
struct dsi_data {int update_channel; scalar_t__ te_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_VC_TE (int const) ; 
 scalar_t__ REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 
 struct dsi_data* dsi_get_dsidrv_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_packet_sent_handler_vp(void *data, u32 mask)
{
	struct dsi_packet_sent_handler_data *vp_data =
		(struct dsi_packet_sent_handler_data *) data;
	struct dsi_data *dsi = dsi_get_dsidrv_data(vp_data->dsidev);
	const int channel = dsi->update_channel;
	u8 bit = dsi->te_enabled ? 30 : 31;

	if (REG_GET(vp_data->dsidev, DSI_VC_TE(channel), bit, bit) == 0)
		complete(vp_data->completion);
}
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
struct dsi_packet_sent_handler_data {int /*<<< orphan*/ * completion; struct dsi_data* dsi; } ;
struct dsi_data {scalar_t__ te_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSI_VC_IRQ_PACKET_SENT ; 
 int /*<<< orphan*/  DSI_VC_TE (int) ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EIO ; 
 scalar_t__ REG_GET (struct dsi_data*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  completion ; 
 int /*<<< orphan*/  dsi_packet_sent_handler_vp ; 
 int dsi_register_isr_vc (struct dsi_data*,int,int /*<<< orphan*/ ,struct dsi_packet_sent_handler_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_unregister_isr_vc (struct dsi_data*,int,int /*<<< orphan*/ ,struct dsi_packet_sent_handler_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsi_sync_vc_vp(struct dsi_data *dsi, int channel)
{
	DECLARE_COMPLETION_ONSTACK(completion);
	struct dsi_packet_sent_handler_data vp_data = {
		.dsi = dsi,
		.completion = &completion
	};
	int r = 0;
	u8 bit;

	bit = dsi->te_enabled ? 30 : 31;

	r = dsi_register_isr_vc(dsi, channel, dsi_packet_sent_handler_vp,
		&vp_data, DSI_VC_IRQ_PACKET_SENT);
	if (r)
		goto err0;

	/* Wait for completion only if TE_EN/TE_START is still set */
	if (REG_GET(dsi, DSI_VC_TE(channel), bit, bit)) {
		if (wait_for_completion_timeout(&completion,
				msecs_to_jiffies(10)) == 0) {
			DSSERR("Failed to complete previous frame transfer\n");
			r = -EIO;
			goto err1;
		}
	}

	dsi_unregister_isr_vc(dsi, channel, dsi_packet_sent_handler_vp,
		&vp_data, DSI_VC_IRQ_PACKET_SENT);

	return 0;
err1:
	dsi_unregister_isr_vc(dsi, channel, dsi_packet_sent_handler_vp,
		&vp_data, DSI_VC_IRQ_PACKET_SENT);
err0:
	return r;
}
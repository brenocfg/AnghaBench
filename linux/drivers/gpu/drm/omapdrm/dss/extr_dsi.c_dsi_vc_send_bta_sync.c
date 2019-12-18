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
typedef  scalar_t__ u32 ;
struct omap_dss_device {int dummy; } ;
struct dsi_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSI_IRQ_ERROR_MASK ; 
 int /*<<< orphan*/  DSI_VC_IRQ_BTA ; 
 int /*<<< orphan*/  DSSERR (char*,...) ; 
 int EIO ; 
 int /*<<< orphan*/  completion ; 
 int /*<<< orphan*/  dsi_completion_handler ; 
 scalar_t__ dsi_get_errors (struct dsi_data*) ; 
 int dsi_register_isr (struct dsi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsi_register_isr_vc (struct dsi_data*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_unregister_isr (struct dsi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_unregister_isr_vc (struct dsi_data*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsi_vc_send_bta (struct dsi_data*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct dsi_data* to_dsi_data (struct omap_dss_device*) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsi_vc_send_bta_sync(struct omap_dss_device *dssdev, int channel)
{
	struct dsi_data *dsi = to_dsi_data(dssdev);
	DECLARE_COMPLETION_ONSTACK(completion);
	int r = 0;
	u32 err;

	r = dsi_register_isr_vc(dsi, channel, dsi_completion_handler,
			&completion, DSI_VC_IRQ_BTA);
	if (r)
		goto err0;

	r = dsi_register_isr(dsi, dsi_completion_handler, &completion,
			DSI_IRQ_ERROR_MASK);
	if (r)
		goto err1;

	r = dsi_vc_send_bta(dsi, channel);
	if (r)
		goto err2;

	if (wait_for_completion_timeout(&completion,
				msecs_to_jiffies(500)) == 0) {
		DSSERR("Failed to receive BTA\n");
		r = -EIO;
		goto err2;
	}

	err = dsi_get_errors(dsi);
	if (err) {
		DSSERR("Error while sending BTA: %x\n", err);
		r = -EIO;
		goto err2;
	}
err2:
	dsi_unregister_isr(dsi, dsi_completion_handler, &completion,
			DSI_IRQ_ERROR_MASK);
err1:
	dsi_unregister_isr_vc(dsi, channel, dsi_completion_handler,
			&completion, DSI_VC_IRQ_BTA);
err0:
	return r;
}
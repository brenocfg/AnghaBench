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
struct mdfld_dsi_dpi_output {int panel_on; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int DSI_DPI_CTRL_HS_TURN_ON ; 
 int DSI_INTR_STATE_SPL_PKG_SENT ; 
 int /*<<< orphan*/  MIPI_DPI_CONTROL_REG (int) ; 
 int /*<<< orphan*/  MIPI_INTR_STAT_REG (int) ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdfld_wait_for_SPL_PKG_SENT (struct drm_device*,int) ; 

void mdfld_dsi_dpi_turn_on(struct mdfld_dsi_dpi_output *output, int pipe)
{
	struct drm_device *dev = output->dev;

	/* clear special packet sent bit */
	if (REG_READ(MIPI_INTR_STAT_REG(pipe)) & DSI_INTR_STATE_SPL_PKG_SENT)
		REG_WRITE(MIPI_INTR_STAT_REG(pipe),
					DSI_INTR_STATE_SPL_PKG_SENT);

	/*send turn on package*/
	REG_WRITE(MIPI_DPI_CONTROL_REG(pipe), DSI_DPI_CTRL_HS_TURN_ON);

	/*wait for SPL_PKG_SENT interrupt*/
	mdfld_wait_for_SPL_PKG_SENT(dev, pipe);

	if (REG_READ(MIPI_INTR_STAT_REG(pipe)) & DSI_INTR_STATE_SPL_PKG_SENT)
		REG_WRITE(MIPI_INTR_STAT_REG(pipe),
					DSI_INTR_STATE_SPL_PKG_SENT);

	output->panel_on = 1;

	/* FIXME the following is disabled to WA the X slow start issue
	   for TMD panel
	if (pipe == 2)
		dev_priv->dpi_panel_on2 = true;
	else if (pipe == 0)
		dev_priv->dpi_panel_on = true; */
}
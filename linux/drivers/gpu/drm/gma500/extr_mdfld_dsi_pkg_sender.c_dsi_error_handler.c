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
typedef  int u32 ;
struct mdfld_dsi_pkg_sender {int mipi_intr_stat_reg; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int REG_READ (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dsi_errors ; 
 int handle_dsi_error (struct mdfld_dsi_pkg_sender*,int) ; 

__attribute__((used)) static int dsi_error_handler(struct mdfld_dsi_pkg_sender *sender)
{
	struct drm_device *dev = sender->dev;
	u32 intr_stat_reg = sender->mipi_intr_stat_reg;
	u32 mask;
	u32 intr_stat;
	int i;
	int err = 0;

	intr_stat = REG_READ(intr_stat_reg);

	for (i = 0; i < 32; i++) {
		mask = (0x00000001UL) << i;
		if (intr_stat & mask) {
			dev_dbg(sender->dev->dev, "[DSI]: %s\n", dsi_errors[i]);
			err = handle_dsi_error(sender, mask);
			if (err)
				DRM_ERROR("Cannot handle error\n");
		}
	}
	return err;
}
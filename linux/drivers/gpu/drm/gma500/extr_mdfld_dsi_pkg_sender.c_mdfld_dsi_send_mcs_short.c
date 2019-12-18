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
typedef  scalar_t__ u8 ;
struct mdfld_dsi_pkg_sender {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 scalar_t__ MIPI_DSI_DCS_SHORT_WRITE ; 
 scalar_t__ MIPI_DSI_DCS_SHORT_WRITE_PARAM ; 
 int /*<<< orphan*/  send_pkg (struct mdfld_dsi_pkg_sender*,scalar_t__,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int mdfld_dsi_send_mcs_short(struct mdfld_dsi_pkg_sender *sender, u8 cmd,
			u8 param, u8 param_num, bool hs)
{
	u8 data[2];
	unsigned long flags;
	u8 data_type;

	if (!sender) {
		DRM_ERROR("Invalid parameter\n");
		return -EINVAL;
	}

	data[0] = cmd;

	if (param_num) {
		data_type = MIPI_DSI_DCS_SHORT_WRITE_PARAM;
		data[1] = param;
	} else {
		data_type = MIPI_DSI_DCS_SHORT_WRITE;
		data[1] = 0;
	}

	spin_lock_irqsave(&sender->lock, flags);
	send_pkg(sender, data_type, data, sizeof(data), hs);
	spin_unlock_irqrestore(&sender->lock, flags);

	return 0;
}
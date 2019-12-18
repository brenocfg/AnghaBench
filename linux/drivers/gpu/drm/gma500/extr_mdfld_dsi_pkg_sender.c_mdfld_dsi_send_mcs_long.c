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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mdfld_dsi_pkg_sender {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MIPI_DSI_DCS_LONG_WRITE ; 
 int /*<<< orphan*/  send_pkg (struct mdfld_dsi_pkg_sender*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int mdfld_dsi_send_mcs_long(struct mdfld_dsi_pkg_sender *sender, u8 *data,
			u32 len, bool hs)
{
	unsigned long flags;

	if (!sender || !data || !len) {
		DRM_ERROR("Invalid parameters\n");
		return -EINVAL;
	}

	spin_lock_irqsave(&sender->lock, flags);
	send_pkg(sender, MIPI_DSI_DCS_LONG_WRITE, data, len, hs);
	spin_unlock_irqrestore(&sender->lock, flags);

	return 0;
}
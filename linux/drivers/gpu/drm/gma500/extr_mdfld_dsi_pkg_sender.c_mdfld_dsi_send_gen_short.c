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
struct mdfld_dsi_pkg_sender {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM ; 
 int MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM ; 
 int MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM ; 
 int /*<<< orphan*/  send_pkg (struct mdfld_dsi_pkg_sender*,int,int*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int mdfld_dsi_send_gen_short(struct mdfld_dsi_pkg_sender *sender, u8 param0,
			u8 param1, u8 param_num, bool hs)
{
	u8 data[2];
	unsigned long flags;
	u8 data_type;

	if (!sender || param_num > 2) {
		DRM_ERROR("Invalid parameter\n");
		return -EINVAL;
	}

	switch (param_num) {
	case 0:
		data_type = MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM;
		data[0] = 0;
		data[1] = 0;
		break;
	case 1:
		data_type = MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM;
		data[0] = param0;
		data[1] = 0;
		break;
	case 2:
		data_type = MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM;
		data[0] = param0;
		data[1] = param1;
		break;
	}

	spin_lock_irqsave(&sender->lock, flags);
	send_pkg(sender, data_type, data, sizeof(data), hs);
	spin_unlock_irqrestore(&sender->lock, flags);

	return 0;
}
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
typedef  int /*<<< orphan*/  u16 ;
struct mdfld_dsi_pkg_sender {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDFLD_DSI_PKG_SENDER_BUSY ; 
 int MIPI_DCS_ENTER_SLEEP_MODE ; 
 int MIPI_DCS_EXIT_SLEEP_MODE ; 
#define  MIPI_DSI_DCS_LONG_WRITE 130 
#define  MIPI_DSI_DCS_SHORT_WRITE 129 
#define  MIPI_DSI_DCS_SHORT_WRITE_PARAM 128 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int send_pkg_prepare(struct mdfld_dsi_pkg_sender *sender, u8 data_type,
			u8 *data, u16 len)
{
	u8 cmd;

	switch (data_type) {
	case MIPI_DSI_DCS_SHORT_WRITE:
	case MIPI_DSI_DCS_SHORT_WRITE_PARAM:
	case MIPI_DSI_DCS_LONG_WRITE:
		cmd = *data;
		break;
	default:
		return 0;
	}

	/*this prevents other package sending while doing msleep*/
	sender->status = MDFLD_DSI_PKG_SENDER_BUSY;

	/*wait for 120 milliseconds in case exit_sleep_mode just be sent*/
	if (unlikely(cmd == MIPI_DCS_ENTER_SLEEP_MODE)) {
		/*TODO: replace it with msleep later*/
		mdelay(120);
	}

	if (unlikely(cmd == MIPI_DCS_EXIT_SLEEP_MODE)) {
		/*TODO: replace it with msleep later*/
		mdelay(120);
	}
	return 0;
}
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
struct sun6i_dsi {int /*<<< orphan*/  regs; } ;
struct mipi_dsi_msg {int type; int rx_len; } ;
struct mipi_dsi_host {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
#define  MIPI_DSI_DCS_LONG_WRITE 132 
#define  MIPI_DSI_DCS_READ 131 
#define  MIPI_DSI_DCS_SHORT_WRITE 130 
#define  MIPI_DSI_DCS_SHORT_WRITE_PARAM 129 
#define  MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM 128 
 int /*<<< orphan*/  SUN6I_DSI_CMD_CTL_REG ; 
 int SUN6I_DSI_CMD_CTL_RX_FLAG ; 
 int SUN6I_DSI_CMD_CTL_RX_OVERFLOW ; 
 int SUN6I_DSI_CMD_CTL_TX_FLAG ; 
 struct sun6i_dsi* host_to_sun6i_dsi (struct mipi_dsi_host*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sun6i_dsi_dcs_read (struct sun6i_dsi*,struct mipi_dsi_msg const*) ; 
 int sun6i_dsi_dcs_write_long (struct sun6i_dsi*,struct mipi_dsi_msg const*) ; 
 int sun6i_dsi_dcs_write_short (struct sun6i_dsi*,struct mipi_dsi_msg const*) ; 
 int /*<<< orphan*/  sun6i_dsi_inst_abort (struct sun6i_dsi*) ; 
 int sun6i_dsi_inst_wait_for_completion (struct sun6i_dsi*) ; 

__attribute__((used)) static ssize_t sun6i_dsi_transfer(struct mipi_dsi_host *host,
				  const struct mipi_dsi_msg *msg)
{
	struct sun6i_dsi *dsi = host_to_sun6i_dsi(host);
	int ret;

	ret = sun6i_dsi_inst_wait_for_completion(dsi);
	if (ret < 0)
		sun6i_dsi_inst_abort(dsi);

	regmap_write(dsi->regs, SUN6I_DSI_CMD_CTL_REG,
		     SUN6I_DSI_CMD_CTL_RX_OVERFLOW |
		     SUN6I_DSI_CMD_CTL_RX_FLAG |
		     SUN6I_DSI_CMD_CTL_TX_FLAG);

	switch (msg->type) {
	case MIPI_DSI_DCS_SHORT_WRITE:
	case MIPI_DSI_DCS_SHORT_WRITE_PARAM:
	case MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM:
		ret = sun6i_dsi_dcs_write_short(dsi, msg);
		break;

	case MIPI_DSI_DCS_LONG_WRITE:
		ret = sun6i_dsi_dcs_write_long(dsi, msg);
		break;

	case MIPI_DSI_DCS_READ:
		if (msg->rx_len == 1) {
			ret = sun6i_dsi_dcs_read(dsi, msg);
			break;
		}
		/* Else, fall through */

	default:
		ret = -EINVAL;
	}

	return ret;
}
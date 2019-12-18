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
struct mipi_dsi_msg {int rx_len; scalar_t__ rx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dsi_long_read_resp(u8 *buf, const struct mipi_dsi_msg *msg)
{
	/* strip out 4 byte dcs header */
	if (msg->rx_buf && msg->rx_len)
		memcpy(msg->rx_buf, buf + 4, msg->rx_len);

	return msg->rx_len;
}
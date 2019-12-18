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
struct rx_status {int frame_status; } ;

/* Variables and functions */
#define  ZD_CCK_PLCP_SIGNAL_11M 131 
#define  ZD_CCK_PLCP_SIGNAL_1M 130 
#define  ZD_CCK_PLCP_SIGNAL_2M 129 
#define  ZD_CCK_PLCP_SIGNAL_5M5 128 
 int /*<<< orphan*/  ZD_CCK_RATE_11M ; 
 int /*<<< orphan*/  ZD_CCK_RATE_1M ; 
 int /*<<< orphan*/  ZD_CCK_RATE_2M ; 
 int /*<<< orphan*/  ZD_CCK_RATE_5_5M ; 
 int ZD_RX_OFDM ; 
 int zd_cck_plcp_header_signal (void const*) ; 
 int /*<<< orphan*/  zd_rate_from_ofdm_plcp_header (void const*) ; 

u8 zd_rx_rate(const void *rx_frame, const struct rx_status *status)
{
	u8 zd_rate;
	if (status->frame_status & ZD_RX_OFDM) {
		zd_rate = zd_rate_from_ofdm_plcp_header(rx_frame);
	} else {
		switch (zd_cck_plcp_header_signal(rx_frame)) {
		case ZD_CCK_PLCP_SIGNAL_1M:
			zd_rate = ZD_CCK_RATE_1M;
			break;
		case ZD_CCK_PLCP_SIGNAL_2M:
			zd_rate = ZD_CCK_RATE_2M;
			break;
		case ZD_CCK_PLCP_SIGNAL_5M5:
			zd_rate = ZD_CCK_RATE_5_5M;
			break;
		case ZD_CCK_PLCP_SIGNAL_11M:
			zd_rate = ZD_CCK_RATE_11M;
			break;
		default:
			zd_rate = 0;
		}
	}

	return zd_rate;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  aux; } ;
struct intel_digital_port {TYPE_1__ dp; } ;
struct hdcp2_rep_send_receiverid_list {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_HDCP_2_2_REG_RXINFO_OFFSET ; 
 int EIO ; 
 int HDCP_2_2_DEV_COUNT_HI (int /*<<< orphan*/ ) ; 
 int HDCP_2_2_DEV_COUNT_LO (int /*<<< orphan*/ ) ; 
 int HDCP_2_2_MAX_DEVICE_COUNT ; 
 int HDCP_2_2_RECEIVER_IDS_MAX_LEN ; 
 int HDCP_2_2_RECEIVER_ID_LEN ; 
 int HDCP_2_2_RXINFO_LEN ; 
 int drm_dp_dpcd_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static
ssize_t get_receiver_id_list_size(struct intel_digital_port *intel_dig_port)
{
	u8 rx_info[HDCP_2_2_RXINFO_LEN];
	u32 dev_cnt;
	ssize_t ret;

	ret = drm_dp_dpcd_read(&intel_dig_port->dp.aux,
			       DP_HDCP_2_2_REG_RXINFO_OFFSET,
			       (void *)rx_info, HDCP_2_2_RXINFO_LEN);
	if (ret != HDCP_2_2_RXINFO_LEN)
		return ret >= 0 ? -EIO : ret;

	dev_cnt = (HDCP_2_2_DEV_COUNT_HI(rx_info[0]) << 4 |
		   HDCP_2_2_DEV_COUNT_LO(rx_info[1]));

	if (dev_cnt > HDCP_2_2_MAX_DEVICE_COUNT)
		dev_cnt = HDCP_2_2_MAX_DEVICE_COUNT;

	ret = sizeof(struct hdcp2_rep_send_receiverid_list) -
		HDCP_2_2_RECEIVER_IDS_MAX_LEN +
		(dev_cnt * HDCP_2_2_RECEIVER_ID_LEN);

	return ret;
}
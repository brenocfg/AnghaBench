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
struct TYPE_2__ {int /*<<< orphan*/  aux; } ;
struct intel_digital_port {TYPE_1__ dp; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_HDCP_2_2_REG_RXSTATUS_OFFSET ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int EIO ; 
 int HDCP_2_2_DP_RXSTATUS_LEN ; 
 int drm_dp_dpcd_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline
int intel_dp_hdcp2_read_rx_status(struct intel_digital_port *intel_dig_port,
				  u8 *rx_status)
{
	ssize_t ret;

	ret = drm_dp_dpcd_read(&intel_dig_port->dp.aux,
			       DP_HDCP_2_2_REG_RXSTATUS_OFFSET, rx_status,
			       HDCP_2_2_DP_RXSTATUS_LEN);
	if (ret != HDCP_2_2_DP_RXSTATUS_LEN) {
		DRM_DEBUG_KMS("Read bstatus from DP/AUX failed (%zd)\n", ret);
		return ret >= 0 ? -EIO : ret;
	}

	return 0;
}
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
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_AUX_HDCP_KSV_FIFO ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,size_t) ; 
 int DRM_HDCP_KSV_LEN ; 
 int EIO ; 
 size_t drm_dp_dpcd_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int min (int,int) ; 

__attribute__((used)) static
int intel_dp_hdcp_read_ksv_fifo(struct intel_digital_port *intel_dig_port,
				int num_downstream, u8 *ksv_fifo)
{
	ssize_t ret;
	int i;

	/* KSV list is read via 15 byte window (3 entries @ 5 bytes each) */
	for (i = 0; i < num_downstream; i += 3) {
		size_t len = min(num_downstream - i, 3) * DRM_HDCP_KSV_LEN;
		ret = drm_dp_dpcd_read(&intel_dig_port->dp.aux,
				       DP_AUX_HDCP_KSV_FIFO,
				       ksv_fifo + i * DRM_HDCP_KSV_LEN,
				       len);
		if (ret != len) {
			DRM_DEBUG_KMS("Read ksv[%d] from DP/AUX failed (%zd)\n",
				      i, ret);
			return ret >= 0 ? -EIO : ret;
		}
	}
	return 0;
}
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
struct anx78xx {int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_GET_SINK_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_SINK_COUNT ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EIO ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int anx78xx_get_downstream_info(struct anx78xx *anx78xx)
{
	u8 value;
	int err;

	err = drm_dp_dpcd_readb(&anx78xx->aux, DP_SINK_COUNT, &value);
	if (err < 0) {
		DRM_ERROR("Get sink count failed %d\n", err);
		return err;
	}

	if (!DP_GET_SINK_COUNT(value)) {
		DRM_ERROR("Downstream disconnected\n");
		return -EIO;
	}

	return 0;
}
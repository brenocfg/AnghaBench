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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ revoked_ksv_cnt; int /*<<< orphan*/  mutex; scalar_t__* revoked_ksv_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 scalar_t__ DRM_HDCP_KSV_LEN ; 
 int /*<<< orphan*/  drm_hdcp_print_ksv (scalar_t__*) ; 
 int /*<<< orphan*/  drm_hdcp_request_srm (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* srm_data ; 

bool drm_hdcp_check_ksvs_revoked(struct drm_device *drm_dev, u8 *ksvs,
				 u32 ksv_count)
{
	u32 rev_ksv_cnt, cnt, i, j;
	u8 *rev_ksv_list;

	if (!srm_data)
		return false;

	mutex_lock(&srm_data->mutex);
	drm_hdcp_request_srm(drm_dev);

	rev_ksv_cnt = srm_data->revoked_ksv_cnt;
	rev_ksv_list = srm_data->revoked_ksv_list;

	/* If the Revoked ksv list is empty */
	if (!rev_ksv_cnt || !rev_ksv_list) {
		mutex_unlock(&srm_data->mutex);
		return false;
	}

	for  (cnt = 0; cnt < ksv_count; cnt++) {
		rev_ksv_list = srm_data->revoked_ksv_list;
		for (i = 0; i < rev_ksv_cnt; i++) {
			for (j = 0; j < DRM_HDCP_KSV_LEN; j++)
				if (ksvs[j] != rev_ksv_list[j]) {
					break;
				} else if (j == (DRM_HDCP_KSV_LEN - 1)) {
					DRM_DEBUG("Revoked KSV is ");
					drm_hdcp_print_ksv(ksvs);
					mutex_unlock(&srm_data->mutex);
					return true;
				}
			/* Move the offset to next KSV in the revoked list */
			rev_ksv_list += DRM_HDCP_KSV_LEN;
		}

		/* Iterate to next ksv_offset */
		ksvs += DRM_HDCP_KSV_LEN;
	}
	mutex_unlock(&srm_data->mutex);
	return false;
}
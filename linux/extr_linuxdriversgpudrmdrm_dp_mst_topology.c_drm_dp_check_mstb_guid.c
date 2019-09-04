#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct drm_dp_mst_branch {int /*<<< orphan*/  guid; TYPE_1__* mgr; scalar_t__ port_parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_GUID ; 
 int drm_dp_dpcd_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int drm_dp_send_dpcd_write (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dp_validate_guid (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void drm_dp_check_mstb_guid(struct drm_dp_mst_branch *mstb, u8 *guid)
{
	int ret;

	memcpy(mstb->guid, guid, 16);

	if (!drm_dp_validate_guid(mstb->mgr, mstb->guid)) {
		if (mstb->port_parent) {
			ret = drm_dp_send_dpcd_write(
					mstb->mgr,
					mstb->port_parent,
					DP_GUID,
					16,
					mstb->guid);
		} else {

			ret = drm_dp_dpcd_write(
					mstb->mgr->aux,
					DP_GUID,
					mstb->guid,
					16);
		}
	}
}
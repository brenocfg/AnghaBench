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
typedef  int u32 ;
struct efa_com_dev {int supported_features; } ;
typedef  enum efa_admin_aq_feature_id { ____Placeholder_efa_admin_aq_feature_id } efa_admin_aq_feature_id ;

/* Variables and functions */
 int EFA_ADMIN_DEVICE_ATTR ; 

__attribute__((used)) static bool
efa_com_check_supported_feature_id(struct efa_com_dev *edev,
				   enum efa_admin_aq_feature_id feature_id)
{
	u32 feature_mask = 1 << feature_id;

	/* Device attributes is always supported */
	if (feature_id != EFA_ADMIN_DEVICE_ATTR &&
	    !(edev->supported_features & feature_mask))
		return false;

	return true;
}
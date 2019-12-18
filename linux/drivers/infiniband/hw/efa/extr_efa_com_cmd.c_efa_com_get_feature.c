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
struct efa_com_dev {int dummy; } ;
struct efa_admin_get_feature_resp {int dummy; } ;
typedef  enum efa_admin_aq_feature_id { ____Placeholder_efa_admin_aq_feature_id } efa_admin_aq_feature_id ;

/* Variables and functions */
 int efa_com_get_feature_ex (struct efa_com_dev*,struct efa_admin_get_feature_resp*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efa_com_get_feature(struct efa_com_dev *edev,
			       struct efa_admin_get_feature_resp *get_resp,
			       enum efa_admin_aq_feature_id feature_id)
{
	return efa_com_get_feature_ex(edev, get_resp, feature_id, 0, 0);
}
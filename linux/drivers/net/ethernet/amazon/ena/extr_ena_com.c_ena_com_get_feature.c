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
struct ena_com_dev {int dummy; } ;
struct ena_admin_get_feat_resp {int dummy; } ;
typedef  enum ena_admin_aq_feature_id { ____Placeholder_ena_admin_aq_feature_id } ena_admin_aq_feature_id ;

/* Variables and functions */
 int ena_com_get_feature_ex (struct ena_com_dev*,struct ena_admin_get_feat_resp*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ena_com_get_feature(struct ena_com_dev *ena_dev,
			       struct ena_admin_get_feat_resp *get_resp,
			       enum ena_admin_aq_feature_id feature_id,
			       u8 feature_ver)
{
	return ena_com_get_feature_ex(ena_dev,
				      get_resp,
				      feature_id,
				      0,
				      0,
				      feature_ver);
}
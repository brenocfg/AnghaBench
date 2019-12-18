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
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int /*<<< orphan*/  u8 ;
struct ib_gid_attr {scalar_t__ gid_type; } ;
struct hns_roce_dev {int /*<<< orphan*/  dev; } ;
typedef  enum hns_roce_sgid_type { ____Placeholder_hns_roce_sgid_type } hns_roce_sgid_type ;

/* Variables and functions */
 int EINVAL ; 
 int GID_TYPE_FLAG_ROCE_V1 ; 
 int GID_TYPE_FLAG_ROCE_V2_IPV4 ; 
 int GID_TYPE_FLAG_ROCE_V2_IPV6 ; 
 scalar_t__ IB_GID_TYPE_ROCE ; 
 scalar_t__ IB_GID_TYPE_ROCE_UDP_ENCAP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int hns_roce_config_sgid_table (struct hns_roce_dev*,int,union ib_gid const*,int) ; 
 scalar_t__ ipv6_addr_v4mapped (void*) ; 

__attribute__((used)) static int hns_roce_v2_set_gid(struct hns_roce_dev *hr_dev, u8 port,
			       int gid_index, const union ib_gid *gid,
			       const struct ib_gid_attr *attr)
{
	enum hns_roce_sgid_type sgid_type = GID_TYPE_FLAG_ROCE_V1;
	int ret;

	if (!gid || !attr)
		return -EINVAL;

	if (attr->gid_type == IB_GID_TYPE_ROCE)
		sgid_type = GID_TYPE_FLAG_ROCE_V1;

	if (attr->gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP) {
		if (ipv6_addr_v4mapped((void *)gid))
			sgid_type = GID_TYPE_FLAG_ROCE_V2_IPV4;
		else
			sgid_type = GID_TYPE_FLAG_ROCE_V2_IPV6;
	}

	ret = hns_roce_config_sgid_table(hr_dev, gid_index, gid, sgid_type);
	if (ret)
		dev_err(hr_dev->dev, "Configure sgid table failed(%d)!\n", ret);

	return ret;
}
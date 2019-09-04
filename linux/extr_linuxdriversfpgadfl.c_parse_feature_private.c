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
struct dfl_fpga_enum_dfl {scalar_t__ ioaddr; } ;
struct build_feature_devs_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  feature_dev; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int EINVAL ; 
 int create_feature_instance (struct build_feature_devs_info*,struct dfl_fpga_enum_dfl*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 scalar_t__ feature_id (scalar_t__) ; 

__attribute__((used)) static int parse_feature_private(struct build_feature_devs_info *binfo,
				 struct dfl_fpga_enum_dfl *dfl,
				 resource_size_t ofst)
{
	if (!binfo->feature_dev) {
		dev_err(binfo->dev, "the private feature %llx does not belong to any AFU.\n",
			(unsigned long long)feature_id(dfl->ioaddr + ofst));
		return -EINVAL;
	}

	return create_feature_instance(binfo, dfl, ofst, 0, 0);
}
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
typedef  scalar_t__ u64 ;
struct dfl_fpga_enum_dfl {scalar_t__ ioaddr; scalar_t__ len; scalar_t__ start; } ;
struct TYPE_2__ {scalar_t__ start; int /*<<< orphan*/  flags; scalar_t__ end; } ;
struct dfl_feature_info {int /*<<< orphan*/  node; scalar_t__ ioaddr; TYPE_1__ mmio_res; scalar_t__ fid; } ;
struct build_feature_devs_info {int /*<<< orphan*/  feature_num; int /*<<< orphan*/  sub_features; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ feature_id (scalar_t__) ; 
 scalar_t__ feature_size (scalar_t__) ; 
 struct dfl_feature_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
create_feature_instance(struct build_feature_devs_info *binfo,
			struct dfl_fpga_enum_dfl *dfl, resource_size_t ofst,
			resource_size_t size, u64 fid)
{
	struct dfl_feature_info *finfo;

	/* read feature size and id if inputs are invalid */
	size = size ? size : feature_size(dfl->ioaddr + ofst);
	fid = fid ? fid : feature_id(dfl->ioaddr + ofst);

	if (dfl->len - ofst < size)
		return -EINVAL;

	finfo = kzalloc(sizeof(*finfo), GFP_KERNEL);
	if (!finfo)
		return -ENOMEM;

	finfo->fid = fid;
	finfo->mmio_res.start = dfl->start + ofst;
	finfo->mmio_res.end = finfo->mmio_res.start + size - 1;
	finfo->mmio_res.flags = IORESOURCE_MEM;
	finfo->ioaddr = dfl->ioaddr + ofst;

	list_add_tail(&finfo->node, &binfo->sub_features);
	binfo->feature_num++;

	return 0;
}
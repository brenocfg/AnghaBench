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
struct iser_reg_resources {scalar_t__ mr_valid; int /*<<< orphan*/  mr; } ;
struct iser_device {struct ib_device* ib_device; } ;
struct ib_pd {int dummy; } ;
struct TYPE_2__ {int device_cap_flags; } ;
struct ib_device {TYPE_1__ attrs; } ;
typedef  enum ib_mr_type { ____Placeholder_ib_mr_type } ib_mr_type ;

/* Variables and functions */
 int IB_DEVICE_SG_GAPS_REG ; 
 int IB_MR_TYPE_MEM_REG ; 
 int IB_MR_TYPE_SG_GAPS ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_alloc_mr (struct ib_pd*,int,unsigned int) ; 
 int /*<<< orphan*/  iser_err (char*,int) ; 

__attribute__((used)) static int
iser_alloc_reg_res(struct iser_device *device,
		   struct ib_pd *pd,
		   struct iser_reg_resources *res,
		   unsigned int size)
{
	struct ib_device *ib_dev = device->ib_device;
	enum ib_mr_type mr_type;
	int ret;

	if (ib_dev->attrs.device_cap_flags & IB_DEVICE_SG_GAPS_REG)
		mr_type = IB_MR_TYPE_SG_GAPS;
	else
		mr_type = IB_MR_TYPE_MEM_REG;

	res->mr = ib_alloc_mr(pd, mr_type, size);
	if (IS_ERR(res->mr)) {
		ret = PTR_ERR(res->mr);
		iser_err("Failed to allocate ib_fast_reg_mr err=%d\n", ret);
		return ret;
	}
	res->mr_valid = 0;

	return 0;
}
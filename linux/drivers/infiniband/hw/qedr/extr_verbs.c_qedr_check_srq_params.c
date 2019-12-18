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
struct qedr_device_attr {scalar_t__ max_srq_wr; scalar_t__ max_sge; } ;
struct qedr_dev {struct qedr_device_attr attr; } ;
struct ib_udata {int dummy; } ;
struct TYPE_2__ {scalar_t__ max_wr; scalar_t__ max_sge; } ;
struct ib_srq_init_attr {TYPE_1__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,scalar_t__,scalar_t__) ; 
 int EINVAL ; 

__attribute__((used)) static int qedr_check_srq_params(struct qedr_dev *dev,
				 struct ib_srq_init_attr *attrs,
				 struct ib_udata *udata)
{
	struct qedr_device_attr *qattr = &dev->attr;

	if (attrs->attr.max_wr > qattr->max_srq_wr) {
		DP_ERR(dev,
		       "create srq: unsupported srq_wr=0x%x requested (max_srq_wr=0x%x)\n",
		       attrs->attr.max_wr, qattr->max_srq_wr);
		return -EINVAL;
	}

	if (attrs->attr.max_sge > qattr->max_sge) {
		DP_ERR(dev,
		       "create srq: unsupported sge=0x%x requested (max_srq_sge=0x%x)\n",
		       attrs->attr.max_sge, qattr->max_sge);
		return -EINVAL;
	}

	return 0;
}
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
struct ib_device_attr {int dummy; } ;
struct TYPE_2__ {struct ib_device_attr props; } ;
struct rvt_dev_info {TYPE_1__ dparms; } ;
struct ib_udata {scalar_t__ outlen; scalar_t__ inlen; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct rvt_dev_info* ib_to_rvt (struct ib_device*) ; 

__attribute__((used)) static int rvt_query_device(struct ib_device *ibdev,
			    struct ib_device_attr *props,
			    struct ib_udata *uhw)
{
	struct rvt_dev_info *rdi = ib_to_rvt(ibdev);

	if (uhw->inlen || uhw->outlen)
		return -EINVAL;
	/*
	 * Return rvt_dev_info.dparms.props contents
	 */
	*props = rdi->dparms.props;
	return 0;
}
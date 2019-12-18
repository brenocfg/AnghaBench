#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  interface_id; int /*<<< orphan*/  subnet_prefix; } ;
union ib_gid {TYPE_2__ global; } ;
typedef  int /*<<< orphan*/  u8 ;
struct rvt_ibport {int /*<<< orphan*/  gid_prefix; } ;
struct TYPE_3__ {int (* get_guid_be ) (struct rvt_dev_info*,struct rvt_ibport*,int,int /*<<< orphan*/ *) ;} ;
struct rvt_dev_info {TYPE_1__ driver_f; struct rvt_ibport** ports; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct rvt_dev_info* ib_to_rvt (struct ib_device*) ; 
 int ibport_num_to_idx (struct ib_device*,int /*<<< orphan*/ ) ; 
 int stub1 (struct rvt_dev_info*,struct rvt_ibport*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rvt_query_gid(struct ib_device *ibdev, u8 port_num,
			 int guid_index, union ib_gid *gid)
{
	struct rvt_dev_info *rdi;
	struct rvt_ibport *rvp;
	int port_index;

	/*
	 * Driver is responsible for updating the guid table. Which will be used
	 * to craft the return value. This will work similar to how query_pkey()
	 * is being done.
	 */
	port_index = ibport_num_to_idx(ibdev, port_num);
	if (port_index < 0)
		return -EINVAL;

	rdi = ib_to_rvt(ibdev);
	rvp = rdi->ports[port_index];

	gid->global.subnet_prefix = rvp->gid_prefix;

	return rdi->driver_f.get_guid_be(rdi, rvp, guid_index,
					 &gid->global.interface_id);
}
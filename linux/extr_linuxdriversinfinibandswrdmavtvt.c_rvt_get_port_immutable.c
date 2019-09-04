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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  max_mad_size; int /*<<< orphan*/  core_cap_flags; } ;
struct rvt_dev_info {TYPE_1__ dparms; } ;
struct ib_port_immutable {int /*<<< orphan*/  max_mad_size; int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  pkey_tbl_len; int /*<<< orphan*/  core_cap_flags; } ;
struct ib_port_attr {int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  pkey_tbl_len; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ib_query_port (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 
 struct rvt_dev_info* ib_to_rvt (struct ib_device*) ; 
 int ibport_num_to_idx (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rvt_get_port_immutable(struct ib_device *ibdev, u8 port_num,
				  struct ib_port_immutable *immutable)
{
	struct rvt_dev_info *rdi = ib_to_rvt(ibdev);
	struct ib_port_attr attr;
	int err, port_index;

	port_index = ibport_num_to_idx(ibdev, port_num);
	if (port_index < 0)
		return -EINVAL;

	immutable->core_cap_flags = rdi->dparms.core_cap_flags;

	err = ib_query_port(ibdev, port_num, &attr);
	if (err)
		return err;

	immutable->pkey_tbl_len = attr.pkey_tbl_len;
	immutable->gid_tbl_len = attr.gid_tbl_len;
	immutable->max_mad_size = rdi->dparms.max_mad_size;

	return 0;
}
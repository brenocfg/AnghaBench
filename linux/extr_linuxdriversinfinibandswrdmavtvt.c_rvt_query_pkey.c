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
typedef  scalar_t__ u16 ;
struct rvt_dev_info {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct rvt_dev_info* ib_to_rvt (struct ib_device*) ; 
 int ibport_num_to_idx (struct ib_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ rvt_get_npkeys (struct rvt_dev_info*) ; 
 scalar_t__ rvt_get_pkey (struct rvt_dev_info*,int,scalar_t__) ; 

__attribute__((used)) static int rvt_query_pkey(struct ib_device *ibdev, u8 port_num, u16 index,
			  u16 *pkey)
{
	/*
	 * Driver will be responsible for keeping rvt_dev_info.pkey_table up to
	 * date. This function will just return that value. There is no need to
	 * lock, if a stale value is read and sent to the user so be it there is
	 * no way to protect against that anyway.
	 */
	struct rvt_dev_info *rdi = ib_to_rvt(ibdev);
	int port_index;

	port_index = ibport_num_to_idx(ibdev, port_num);
	if (port_index < 0)
		return -EINVAL;

	if (index >= rvt_get_npkeys(rdi))
		return -EINVAL;

	*pkey = rvt_get_pkey(rdi, port_index, index);
	return 0;
}
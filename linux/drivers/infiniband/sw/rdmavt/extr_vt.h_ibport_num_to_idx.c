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
typedef  int u8 ;
struct TYPE_2__ {int nports; } ;
struct rvt_dev_info {TYPE_1__ dparms; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct rvt_dev_info* ib_to_rvt (struct ib_device*) ; 

__attribute__((used)) static inline int ibport_num_to_idx(struct ib_device *ibdev, u8 port_num)
{
	struct rvt_dev_info *rdi = ib_to_rvt(ibdev);
	int port_index;

	port_index = port_num - 1; /* IB ports start at 1 our arrays at 0 */
	if ((port_index < 0) || (port_index >= rdi->dparms.nports))
		return -EINVAL;

	return port_index;
}
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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int num_ports; TYPE_2__* spec_qps; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct TYPE_4__ {int qp0_proxy; int qp0_tunnel; int /*<<< orphan*/  qp0_qkey; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int vf_get_qp0_qkey(struct mlx4_dev *dev, int qpn, u32 *qkey)
{
	int i;
	for (i = 0; i < dev->caps.num_ports; i++) {
		if (qpn == dev->caps.spec_qps[i].qp0_proxy ||
		    qpn == dev->caps.spec_qps[i].qp0_tunnel) {
			*qkey = dev->caps.spec_qps[i].qp0_qkey;
			return 0;
		}
	}
	return -EINVAL;
}
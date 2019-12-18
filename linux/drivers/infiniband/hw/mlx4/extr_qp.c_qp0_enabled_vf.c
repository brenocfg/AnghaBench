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
struct TYPE_4__ {int num_ports; TYPE_1__* spec_qps; } ;
struct mlx4_dev {TYPE_2__ caps; } ;
struct TYPE_3__ {int qp0_proxy; int /*<<< orphan*/  qp0_qkey; } ;

/* Variables and functions */

__attribute__((used)) static int qp0_enabled_vf(struct mlx4_dev *dev, int qpn)
{
	int i;
	for (i = 0; i < dev->caps.num_ports; i++) {
		if (qpn == dev->caps.spec_qps[i].qp0_proxy)
			return !!dev->caps.spec_qps[i].qp0_qkey;
	}
	return 0;
}
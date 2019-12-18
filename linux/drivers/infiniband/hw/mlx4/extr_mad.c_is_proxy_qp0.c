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
struct mlx4_ib_dev {TYPE_2__* dev; } ;
struct TYPE_3__ {int base_proxy_sqpn; } ;
struct TYPE_4__ {TYPE_1__ phys_caps; } ;

/* Variables and functions */

__attribute__((used)) static int is_proxy_qp0(struct mlx4_ib_dev *dev, int qpn, int slave)
{
	int proxy_start = dev->dev->phys_caps.base_proxy_sqpn + 8 * slave;

	return (qpn >= proxy_start && qpn <= proxy_start + 1);
}
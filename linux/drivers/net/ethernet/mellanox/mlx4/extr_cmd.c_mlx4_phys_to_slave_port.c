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
struct TYPE_2__ {int /*<<< orphan*/  num_ports; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_active_ports {int /*<<< orphan*/  ports; } ;

/* Variables and functions */
 int find_first_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx4_active_ports mlx4_get_active_ports (struct mlx4_dev*,int) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

int mlx4_phys_to_slave_port(struct mlx4_dev *dev, int slave, int port)
{
	struct mlx4_active_ports actv_ports = mlx4_get_active_ports(dev, slave);
	if (test_bit(port - 1, actv_ports.ports))
		return port -
			find_first_bit(actv_ports.ports, dev->caps.num_ports);

	return -1;
}
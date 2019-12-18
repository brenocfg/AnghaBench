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
typedef  int u8 ;
struct mlx5_ib_dev {scalar_t__ is_rep; } ;

/* Variables and functions */
 int __get_port_caps (struct mlx5_ib_dev*,int) ; 

__attribute__((used)) static int get_port_caps(struct mlx5_ib_dev *dev, u8 port)
{
	/* For representors use port 1, is this is the only native
	 * port
	 */
	if (dev->is_rep)
		return __get_port_caps(dev, 1);
	return __get_port_caps(dev, port);
}
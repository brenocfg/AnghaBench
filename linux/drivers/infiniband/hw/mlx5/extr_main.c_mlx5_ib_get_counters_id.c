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
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_ib_dev {int dummy; } ;
struct mlx5_ib_counters {int /*<<< orphan*/  set_id; } ;

/* Variables and functions */
 struct mlx5_ib_counters* get_counters (struct mlx5_ib_dev*,int /*<<< orphan*/ ) ; 

u16 mlx5_ib_get_counters_id(struct mlx5_ib_dev *dev, u8 port_num)
{
	const struct mlx5_ib_counters *cnts = get_counters(dev, port_num);

	return cnts->set_id;
}
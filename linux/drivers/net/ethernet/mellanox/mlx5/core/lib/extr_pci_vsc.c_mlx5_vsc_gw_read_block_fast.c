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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ mlx5_vsc_gw_read_fast (struct mlx5_core_dev*,unsigned int,unsigned int*,int /*<<< orphan*/ *) ; 

int mlx5_vsc_gw_read_block_fast(struct mlx5_core_dev *dev, u32 *data,
				int length)
{
	unsigned int next_read_addr = 0;
	unsigned int read_addr = 0;

	while (read_addr < length) {
		if (mlx5_vsc_gw_read_fast(dev, read_addr, &next_read_addr,
					  &data[(read_addr >> 2)]))
			return read_addr;

		read_addr = next_read_addr;
	}
	return length;
}
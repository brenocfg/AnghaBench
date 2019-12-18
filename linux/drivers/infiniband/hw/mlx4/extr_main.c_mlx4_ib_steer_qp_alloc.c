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
struct mlx4_ib_dev {int steer_qpn_base; int /*<<< orphan*/  steer_qpn_count; int /*<<< orphan*/  ib_uc_qpns_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int bitmap_find_free_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_count_order (int) ; 

int mlx4_ib_steer_qp_alloc(struct mlx4_ib_dev *dev, int count, int *qpn)
{
	int offset;

	WARN_ON(!dev->ib_uc_qpns_bitmap);

	offset = bitmap_find_free_region(dev->ib_uc_qpns_bitmap,
					 dev->steer_qpn_count,
					 get_count_order(count));
	if (offset < 0)
		return offset;

	*qpn = dev->steer_qpn_base + offset;
	return 0;
}
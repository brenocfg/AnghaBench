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
struct mlx5_fc_bulk {int /*<<< orphan*/  bulk_len; int /*<<< orphan*/  bitmask; } ;

/* Variables and functions */
 int bitmap_weight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5_fc_bulk_get_free_fcs_amount(struct mlx5_fc_bulk *bulk)
{
	return bitmap_weight(bulk->bitmask, bulk->bulk_len);
}
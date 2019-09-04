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
typedef  int u64 ;
struct mlx4_mtt {scalar_t__ offset; } ;
struct TYPE_2__ {int mtt_entry_sz; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */

u64 mlx4_mtt_addr(struct mlx4_dev *dev, struct mlx4_mtt *mtt)
{
	return (u64) mtt->offset * dev->caps.mtt_entry_sz;
}
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
typedef  scalar_t__ u16 ;
struct i40iw_vsi_pestat {int /*<<< orphan*/  lock; int /*<<< orphan*/  hw; } ;
struct i40iw_sc_dev {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_hw_stats_init (struct i40iw_vsi_pestat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i40iw_vf_init_pestat(struct i40iw_sc_dev *dev, struct i40iw_vsi_pestat *stats, u16 index)
{
	stats->hw = dev->hw;
	i40iw_hw_stats_init(stats, (u8)index, false);
	spin_lock_init(&stats->lock);
}
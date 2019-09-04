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
typedef  int /*<<< orphan*/  u64 ;
struct mlx5_clock {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */

__attribute__((used)) static inline ktime_t mlx5_timecounter_cyc2time(struct mlx5_clock *clock,
						u64 timestamp)
{
	return 0;
}
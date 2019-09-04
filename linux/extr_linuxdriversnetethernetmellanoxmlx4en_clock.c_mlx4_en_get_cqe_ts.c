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
typedef  int u64 ;
struct mlx4_ts_cqe {int /*<<< orphan*/  timestamp_hi; int /*<<< orphan*/  timestamp_lo; } ;
struct mlx4_cqe {int dummy; } ;

/* Variables and functions */
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 

u64 mlx4_en_get_cqe_ts(struct mlx4_cqe *cqe)
{
	u64 hi, lo;
	struct mlx4_ts_cqe *ts_cqe = (struct mlx4_ts_cqe *)cqe;

	lo = (u64)be16_to_cpu(ts_cqe->timestamp_lo);
	hi = ((u64)be32_to_cpu(ts_cqe->timestamp_hi) + !lo) << 16;

	return hi | lo;
}
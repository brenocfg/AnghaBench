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
struct TYPE_2__ {int* reserved_qps_cnt; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 size_t MLX4_QP_REGION_FW ; 

__attribute__((used)) static int fw_reserved(struct mlx4_dev *dev, int qpn)
{
	return qpn < dev->caps.reserved_qps_cnt[MLX4_QP_REGION_FW];
}
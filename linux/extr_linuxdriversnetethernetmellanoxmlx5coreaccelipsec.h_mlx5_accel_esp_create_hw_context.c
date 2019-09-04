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
struct mlx5_core_dev {int dummy; } ;
struct mlx5_accel_esp_xfrm {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */

__attribute__((used)) static inline void *
mlx5_accel_esp_create_hw_context(struct mlx5_core_dev *mdev,
				 struct mlx5_accel_esp_xfrm *xfrm,
				 const __be32 saddr[4],
				 const __be32 daddr[4],
				 const __be32 spi, bool is_ipv6)
{
	return NULL;
}
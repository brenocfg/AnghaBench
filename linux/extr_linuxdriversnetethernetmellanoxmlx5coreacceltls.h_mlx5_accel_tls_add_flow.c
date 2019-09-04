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
struct tls_crypto_info {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 

__attribute__((used)) static inline int
mlx5_accel_tls_add_flow(struct mlx5_core_dev *mdev, void *flow,
			struct tls_crypto_info *crypto_info,
			u32 start_offload_tcp_sn, u32 *p_swid,
			bool direction_sx) { return -ENOTSUPP; }
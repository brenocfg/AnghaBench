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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx5dr_domain {int dummy; } ;
struct mlx5dr_action {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct mlx5dr_action *
mlx5dr_action_create_dest_vport(struct mlx5dr_domain *domain,
				u32 vport, u8 vhca_id_valid,
				u16 vhca_id) { return NULL; }
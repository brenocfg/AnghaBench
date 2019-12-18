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
struct mlx5dr_domain {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void
mlx5dr_domain_set_peer(struct mlx5dr_domain *dmn,
		       struct mlx5dr_domain *peer_dmn) { }
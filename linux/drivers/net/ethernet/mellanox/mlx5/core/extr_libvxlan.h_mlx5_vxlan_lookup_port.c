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
typedef  int /*<<< orphan*/  u16 ;
struct mx5_vxlan_port {int dummy; } ;
struct mlx5_vxlan {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct mx5_vxlan_port*
mlx5_vxlan_lookup_port(struct mlx5_vxlan *vxlan, u16 port) { return NULL; }
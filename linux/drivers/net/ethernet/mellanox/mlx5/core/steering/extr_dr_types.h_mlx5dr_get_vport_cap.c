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
typedef  size_t u32 ;
struct mlx5dr_cmd_vport_cap {int dummy; } ;
struct mlx5dr_cmd_caps {size_t num_vports; struct mlx5dr_cmd_vport_cap* vports_caps; } ;

/* Variables and functions */
 size_t WIRE_PORT ; 

__attribute__((used)) static inline struct mlx5dr_cmd_vport_cap *
mlx5dr_get_vport_cap(struct mlx5dr_cmd_caps *caps, u32 vport)
{
	if (!caps->vports_caps ||
	    (vport >= caps->num_vports && vport != WIRE_PORT))
		return NULL;

	if (vport == WIRE_PORT)
		vport = caps->num_vports;

	return &caps->vports_caps[vport];
}
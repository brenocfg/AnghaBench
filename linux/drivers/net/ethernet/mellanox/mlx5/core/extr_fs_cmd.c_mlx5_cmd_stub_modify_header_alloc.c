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
struct mlx5_modify_hdr {int dummy; } ;
struct mlx5_flow_root_namespace {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int mlx5_cmd_stub_modify_header_alloc(struct mlx5_flow_root_namespace *ns,
					     u8 namespace, u8 num_actions,
					     void *modify_actions,
					     struct mlx5_modify_hdr *modify_hdr)
{
	return 0;
}
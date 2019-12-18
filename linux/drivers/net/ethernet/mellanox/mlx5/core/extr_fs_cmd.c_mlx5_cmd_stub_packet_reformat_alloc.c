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
struct mlx5_pkt_reformat {int dummy; } ;
struct mlx5_flow_root_namespace {int dummy; } ;
typedef  enum mlx5_flow_namespace_type { ____Placeholder_mlx5_flow_namespace_type } mlx5_flow_namespace_type ;

/* Variables and functions */

__attribute__((used)) static int mlx5_cmd_stub_packet_reformat_alloc(struct mlx5_flow_root_namespace *ns,
					       int reformat_type,
					       size_t size,
					       void *reformat_data,
					       enum mlx5_flow_namespace_type namespace,
					       struct mlx5_pkt_reformat *pkt_reformat)
{
	return 0;
}
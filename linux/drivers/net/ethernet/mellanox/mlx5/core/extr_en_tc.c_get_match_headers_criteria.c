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
typedef  int u32 ;
struct mlx5_flow_spec {int /*<<< orphan*/  match_criteria; } ;

/* Variables and functions */
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_FLOW_CONTEXT_ACTION_DECAP ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/  inner_headers ; 
 int /*<<< orphan*/  outer_headers ; 

__attribute__((used)) static void *get_match_headers_criteria(u32 flags,
					struct mlx5_flow_spec *spec)
{
	return (flags & MLX5_FLOW_CONTEXT_ACTION_DECAP) ?
		MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
			     inner_headers) :
		MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
			     outer_headers);
}
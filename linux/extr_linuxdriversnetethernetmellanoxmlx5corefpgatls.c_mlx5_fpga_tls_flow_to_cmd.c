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

/* Variables and functions */
 int /*<<< orphan*/  MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_BYTE_OFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_GET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  direction_sx ; 
 int /*<<< orphan*/  ipv6 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  src_port ; 
 int /*<<< orphan*/  tls_cmd ; 
 int /*<<< orphan*/  tls_flow ; 

__attribute__((used)) static void mlx5_fpga_tls_flow_to_cmd(void *flow, void *cmd)
{
	memcpy(MLX5_ADDR_OF(tls_cmd, cmd, src_port), flow,
	       MLX5_BYTE_OFF(tls_flow, ipv6));

	MLX5_SET(tls_cmd, cmd, ipv6, MLX5_GET(tls_flow, flow, ipv6));
	MLX5_SET(tls_cmd, cmd, direction_sx,
		 MLX5_GET(tls_flow, flow, direction_sx));
}
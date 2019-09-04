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
struct sock {int dummy; } ;
struct inet_sock {int /*<<< orphan*/  inet_dport; int /*<<< orphan*/  inet_sport; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_FLD_SZ_BYTES (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_port ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  src_port ; 
 int /*<<< orphan*/  tls_flow ; 

__attribute__((used)) static void mlx5e_tls_set_flow_tcp_ports(void *flow, struct sock *sk)
{
	struct inet_sock *inet = inet_sk(sk);

	memcpy(MLX5_ADDR_OF(tls_flow, flow, src_port), &inet->inet_sport,
	       MLX5_FLD_SZ_BYTES(tls_flow, src_port));
	memcpy(MLX5_ADDR_OF(tls_flow, flow, dst_port), &inet->inet_dport,
	       MLX5_FLD_SZ_BYTES(tls_flow, dst_port));
}
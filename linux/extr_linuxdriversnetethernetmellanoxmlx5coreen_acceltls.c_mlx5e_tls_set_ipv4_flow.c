#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct inet_sock {int /*<<< orphan*/  inet_rcv_saddr; int /*<<< orphan*/  inet_daddr; } ;
struct TYPE_5__ {int /*<<< orphan*/  ipv4; } ;
struct TYPE_8__ {TYPE_1__ ipv4_layout; } ;
struct TYPE_6__ {int /*<<< orphan*/  ipv4; } ;
struct TYPE_7__ {TYPE_2__ ipv4_layout; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_FLD_SZ_BYTES (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ dst_ipv4_dst_ipv6 ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ipv4 ; 
 int /*<<< orphan*/  ipv4_layout ; 
 int /*<<< orphan*/  ipv6 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__ src_ipv4_src_ipv6 ; 
 int /*<<< orphan*/  tls_flow ; 

__attribute__((used)) static void mlx5e_tls_set_ipv4_flow(void *flow, struct sock *sk)
{
	struct inet_sock *inet = inet_sk(sk);

	MLX5_SET(tls_flow, flow, ipv6, 0);
	memcpy(MLX5_ADDR_OF(tls_flow, flow, dst_ipv4_dst_ipv6.ipv4_layout.ipv4),
	       &inet->inet_daddr, MLX5_FLD_SZ_BYTES(ipv4_layout, ipv4));
	memcpy(MLX5_ADDR_OF(tls_flow, flow, src_ipv4_src_ipv6.ipv4_layout.ipv4),
	       &inet->inet_rcv_saddr, MLX5_FLD_SZ_BYTES(ipv4_layout, ipv4));
}
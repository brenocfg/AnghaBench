#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_protocol; int /*<<< orphan*/  sk_bound_dev_if; } ;
struct rtable {int dummy; } ;
struct flowi4 {int /*<<< orphan*/  flowi4_proto; int /*<<< orphan*/  flowi4_tos; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  flowi4_oif; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  inet_saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_CONN_FLAGS (struct sock const*) ; 
 TYPE_1__* inet_sk (struct sock const*) ; 
 struct rtable* ip_route_output_key (int /*<<< orphan*/ ,struct flowi4*) ; 
 int /*<<< orphan*/  memset (struct flowi4*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock_net (struct sock const*) ; 

__attribute__((used)) static struct rtable *ip4_route_output_gtp(struct flowi4 *fl4,
					   const struct sock *sk,
					   __be32 daddr)
{
	memset(fl4, 0, sizeof(*fl4));
	fl4->flowi4_oif		= sk->sk_bound_dev_if;
	fl4->daddr		= daddr;
	fl4->saddr		= inet_sk(sk)->inet_saddr;
	fl4->flowi4_tos		= RT_CONN_FLAGS(sk);
	fl4->flowi4_proto	= sk->sk_protocol;

	return ip_route_output_key(sock_net(sk), fl4);
}
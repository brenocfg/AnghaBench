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
struct sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ icsk_bind_hash; } ;

/* Variables and functions */
 TYPE_1__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_put_port (struct sock*) ; 

__attribute__((used)) static void release_tcp_port(struct sock *sk)
{
	if (inet_csk(sk)->icsk_bind_hash)
		inet_put_port(sk);
}
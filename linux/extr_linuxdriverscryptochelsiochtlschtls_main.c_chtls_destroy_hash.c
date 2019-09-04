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
struct tls_device {int dummy; } ;
struct sock {scalar_t__ sk_state; } ;

/* Variables and functions */
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  chtls_stop_listen (struct sock*) ; 

__attribute__((used)) static void chtls_destroy_hash(struct tls_device *dev, struct sock *sk)
{
	if (sk->sk_state == TCP_LISTEN)
		chtls_stop_listen(sk);
}
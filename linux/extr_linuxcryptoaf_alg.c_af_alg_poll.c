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
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct file {int dummy; } ;
struct alg_sock {struct af_alg_ctx* private; } ;
struct af_alg_ctx {scalar_t__ used; int /*<<< orphan*/  more; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRBAND ; 
 int EPOLLWRNORM ; 
 scalar_t__ af_alg_writable (struct sock*) ; 
 struct alg_sock* alg_sk (struct sock*) ; 
 int /*<<< orphan*/  sock_poll_wait (struct file*,struct socket*,int /*<<< orphan*/ *) ; 

__poll_t af_alg_poll(struct file *file, struct socket *sock,
			 poll_table *wait)
{
	struct sock *sk = sock->sk;
	struct alg_sock *ask = alg_sk(sk);
	struct af_alg_ctx *ctx = ask->private;
	__poll_t mask;

	sock_poll_wait(file, sock, wait);
	mask = 0;

	if (!ctx->more || ctx->used)
		mask |= EPOLLIN | EPOLLRDNORM;

	if (af_alg_writable(sk))
		mask |= EPOLLOUT | EPOLLWRNORM | EPOLLWRBAND;

	return mask;
}
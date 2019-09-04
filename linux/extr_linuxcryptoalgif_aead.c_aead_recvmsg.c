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
struct msghdr {int dummy; } ;

/* Variables and functions */
 int EBADMSG ; 
 int EIOCBQUEUED ; 
 int _aead_recvmsg (struct socket*,struct msghdr*,size_t,int) ; 
 int /*<<< orphan*/  af_alg_wmem_wakeup (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 scalar_t__ msg_data_left (struct msghdr*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static int aead_recvmsg(struct socket *sock, struct msghdr *msg,
			size_t ignored, int flags)
{
	struct sock *sk = sock->sk;
	int ret = 0;

	lock_sock(sk);
	while (msg_data_left(msg)) {
		int err = _aead_recvmsg(sock, msg, ignored, flags);

		/*
		 * This error covers -EIOCBQUEUED which implies that we can
		 * only handle one AIO request. If the caller wants to have
		 * multiple AIO requests in parallel, he must make multiple
		 * separate AIO calls.
		 *
		 * Also return the error if no data has been processed so far.
		 */
		if (err <= 0) {
			if (err == -EIOCBQUEUED || err == -EBADMSG || !ret)
				ret = err;
			goto out;
		}

		ret += err;
	}

out:
	af_alg_wmem_wakeup(sk);
	release_sock(sk);
	return ret;
}
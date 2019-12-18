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
struct socket {struct sock* sk; } ;
struct sockaddr_mISDN {scalar_t__ family; int /*<<< orphan*/  dev; } ;
struct sockaddr {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_state; } ;
struct TYPE_2__ {scalar_t__ dev; } ;

/* Variables and functions */
 scalar_t__ AF_ISDN ; 
 int EALREADY ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  MISDN_BOUND ; 
 TYPE_1__* _pms (struct sock*) ; 
 scalar_t__ get_mdevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static int
base_sock_bind(struct socket *sock, struct sockaddr *addr, int addr_len)
{
	struct sockaddr_mISDN *maddr = (struct sockaddr_mISDN *) addr;
	struct sock *sk = sock->sk;
	int err = 0;

	if (addr_len < sizeof(struct sockaddr_mISDN))
		return -EINVAL;

	if (!maddr || maddr->family != AF_ISDN)
		return -EINVAL;

	lock_sock(sk);

	if (_pms(sk)->dev) {
		err = -EALREADY;
		goto done;
	}

	_pms(sk)->dev = get_mdevice(maddr->dev);
	if (!_pms(sk)->dev) {
		err = -ENODEV;
		goto done;
	}
	sk->sk_state = MISDN_BOUND;

done:
	release_sock(sk);
	return err;
}
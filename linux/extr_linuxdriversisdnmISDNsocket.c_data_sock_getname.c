#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct sockaddr_mISDN {int sapi; int tei; int /*<<< orphan*/  channel; int /*<<< orphan*/  dev; int /*<<< orphan*/  family; } ;
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;
struct TYPE_5__ {int addr; int /*<<< orphan*/  nr; } ;
struct TYPE_6__ {TYPE_2__ ch; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_ISDN ; 
 int EBADFD ; 
 TYPE_3__* _pms (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static int
data_sock_getname(struct socket *sock, struct sockaddr *addr,
		  int peer)
{
	struct sockaddr_mISDN	*maddr = (struct sockaddr_mISDN *) addr;
	struct sock		*sk = sock->sk;

	if (!_pms(sk)->dev)
		return -EBADFD;

	lock_sock(sk);

	maddr->family = AF_ISDN;
	maddr->dev = _pms(sk)->dev->id;
	maddr->channel = _pms(sk)->ch.nr;
	maddr->sapi = _pms(sk)->ch.addr & 0xff;
	maddr->tei = (_pms(sk)->ch.addr >> 8) & 0xff;
	release_sock(sk);
	return sizeof(*maddr);
}
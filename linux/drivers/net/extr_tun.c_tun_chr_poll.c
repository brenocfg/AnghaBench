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
struct tun_struct {TYPE_3__* dev; } ;
struct TYPE_4__ {struct sock* sk; } ;
struct tun_file {int /*<<< orphan*/  tx_ring; TYPE_1__ socket; } ;
struct sock {TYPE_2__* sk_socket; } ;
struct file {struct tun_file* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_6__ {scalar_t__ reg_state; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  KERN_INFO ; 
 scalar_t__ NETREG_REGISTERED ; 
 int /*<<< orphan*/  SOCKWQ_ASYNC_NOSPACE ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptr_ring_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tun_debug (int /*<<< orphan*/ ,struct tun_struct*,char*) ; 
 struct tun_struct* tun_get (struct tun_file*) ; 
 int /*<<< orphan*/  tun_put (struct tun_struct*) ; 
 scalar_t__ tun_sock_writeable (struct tun_struct*,struct tun_file*) ; 

__attribute__((used)) static __poll_t tun_chr_poll(struct file *file, poll_table *wait)
{
	struct tun_file *tfile = file->private_data;
	struct tun_struct *tun = tun_get(tfile);
	struct sock *sk;
	__poll_t mask = 0;

	if (!tun)
		return EPOLLERR;

	sk = tfile->socket.sk;

	tun_debug(KERN_INFO, tun, "tun_chr_poll\n");

	poll_wait(file, sk_sleep(sk), wait);

	if (!ptr_ring_empty(&tfile->tx_ring))
		mask |= EPOLLIN | EPOLLRDNORM;

	/* Make sure SOCKWQ_ASYNC_NOSPACE is set if not writable to
	 * guarantee EPOLLOUT to be raised by either here or
	 * tun_sock_write_space(). Then process could get notification
	 * after it writes to a down device and meets -EIO.
	 */
	if (tun_sock_writeable(tun, tfile) ||
	    (!test_and_set_bit(SOCKWQ_ASYNC_NOSPACE, &sk->sk_socket->flags) &&
	     tun_sock_writeable(tun, tfile)))
		mask |= EPOLLOUT | EPOLLWRNORM;

	if (tun->dev->reg_state != NETREG_REGISTERED)
		mask = EPOLLERR;

	tun_put(tun);
	return mask;
}
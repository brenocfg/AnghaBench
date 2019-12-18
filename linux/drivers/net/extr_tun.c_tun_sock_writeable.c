#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tun_struct {TYPE_2__* dev; } ;
struct TYPE_3__ {struct sock* sk; } ;
struct tun_file {TYPE_1__ socket; } ;
struct sock {int dummy; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int IFF_UP ; 
 scalar_t__ sock_writeable (struct sock*) ; 

__attribute__((used)) static bool tun_sock_writeable(struct tun_struct *tun, struct tun_file *tfile)
{
	struct sock *sk = tfile->socket.sk;

	return (tun->dev->flags & IFF_UP) && sock_writeable(sk);
}
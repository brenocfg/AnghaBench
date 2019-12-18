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
struct tun_struct {int numqueues; int filter_attached; int /*<<< orphan*/  fprog; int /*<<< orphan*/ * tfiles; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;
struct tun_file {TYPE_1__ socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (int /*<<< orphan*/ ) ; 
 struct tun_file* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int sk_attach_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tun_detach_filter (struct tun_struct*,int) ; 

__attribute__((used)) static int tun_attach_filter(struct tun_struct *tun)
{
	int i, ret = 0;
	struct tun_file *tfile;

	for (i = 0; i < tun->numqueues; i++) {
		tfile = rtnl_dereference(tun->tfiles[i]);
		lock_sock(tfile->socket.sk);
		ret = sk_attach_filter(&tun->fprog, tfile->socket.sk);
		release_sock(tfile->socket.sk);
		if (ret) {
			tun_detach_filter(tun, i);
			return ret;
		}
	}

	tun->filter_attached = true;
	return ret;
}
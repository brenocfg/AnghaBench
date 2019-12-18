#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  sk_sndbuf; int /*<<< orphan*/  sk_write_space; } ;
struct TYPE_9__ {int /*<<< orphan*/  wait; } ;
struct TYPE_11__ {int /*<<< orphan*/ * ops; struct file* file; TYPE_2__ wq; } ;
struct tun_file {TYPE_3__ sk; int /*<<< orphan*/  next; TYPE_4__ socket; scalar_t__ ifindex; scalar_t__ flags; int /*<<< orphan*/  tun; int /*<<< orphan*/  napi_mutex; int /*<<< orphan*/  tx_ring; } ;
struct net {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct tun_file* private_data; } ;
struct TYPE_12__ {TYPE_1__* nsproxy; } ;
struct TYPE_8__ {struct net* net_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  DBG1 (int /*<<< orphan*/ ,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCK_ZEROCOPY ; 
 TYPE_7__* current ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ ptr_ring_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_free (TYPE_3__*) ; 
 int /*<<< orphan*/  sock_init_data (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  sock_set_flag (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tun_proto ; 
 int /*<<< orphan*/  tun_sock_write_space ; 
 int /*<<< orphan*/  tun_socket_ops ; 

__attribute__((used)) static int tun_chr_open(struct inode *inode, struct file * file)
{
	struct net *net = current->nsproxy->net_ns;
	struct tun_file *tfile;

	DBG1(KERN_INFO, "tunX: tun_chr_open\n");

	tfile = (struct tun_file *)sk_alloc(net, AF_UNSPEC, GFP_KERNEL,
					    &tun_proto, 0);
	if (!tfile)
		return -ENOMEM;
	if (ptr_ring_init(&tfile->tx_ring, 0, GFP_KERNEL)) {
		sk_free(&tfile->sk);
		return -ENOMEM;
	}

	mutex_init(&tfile->napi_mutex);
	RCU_INIT_POINTER(tfile->tun, NULL);
	tfile->flags = 0;
	tfile->ifindex = 0;

	init_waitqueue_head(&tfile->socket.wq.wait);

	tfile->socket.file = file;
	tfile->socket.ops = &tun_socket_ops;

	sock_init_data(&tfile->socket, &tfile->sk);

	tfile->sk.sk_write_space = tun_sock_write_space;
	tfile->sk.sk_sndbuf = INT_MAX;

	file->private_data = tfile;
	INIT_LIST_HEAD(&tfile->next);

	sock_set_flag(&tfile->sk, SOCK_ZEROCOPY);

	return 0;
}
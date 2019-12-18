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
struct xdp_frame {int dummy; } ;
struct tun_struct {int dummy; } ;
struct tun_file {int dummy; } ;
struct sk_buff {int dummy; } ;
struct iov_iter {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  tun_debug (int /*<<< orphan*/ ,struct tun_struct*,char*) ; 
 scalar_t__ tun_is_xdp_frame (void*) ; 
 int /*<<< orphan*/  tun_ptr_free (void*) ; 
 struct xdp_frame* tun_ptr_to_xdp (void*) ; 
 int tun_put_user (struct tun_struct*,struct tun_file*,struct sk_buff*,struct iov_iter*) ; 
 int tun_put_user_xdp (struct tun_struct*,struct tun_file*,struct xdp_frame*,struct iov_iter*) ; 
 void* tun_ring_recv (struct tun_file*,int,int*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdp_return_frame (struct xdp_frame*) ; 

__attribute__((used)) static ssize_t tun_do_read(struct tun_struct *tun, struct tun_file *tfile,
			   struct iov_iter *to,
			   int noblock, void *ptr)
{
	ssize_t ret;
	int err;

	tun_debug(KERN_INFO, tun, "tun_do_read\n");

	if (!iov_iter_count(to)) {
		tun_ptr_free(ptr);
		return 0;
	}

	if (!ptr) {
		/* Read frames from ring */
		ptr = tun_ring_recv(tfile, noblock, &err);
		if (!ptr)
			return err;
	}

	if (tun_is_xdp_frame(ptr)) {
		struct xdp_frame *xdpf = tun_ptr_to_xdp(ptr);

		ret = tun_put_user_xdp(tun, tfile, xdpf, to);
		xdp_return_frame(xdpf);
	} else {
		struct sk_buff *skb = ptr;

		ret = tun_put_user(tun, tfile, skb, to);
		if (unlikely(ret < 0))
			kfree_skb(skb);
		else
			consume_skb(skb);
	}

	return ret;
}
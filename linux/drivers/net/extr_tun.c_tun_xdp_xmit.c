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
typedef  size_t u32 ;
struct xdp_frame {int dummy; } ;
struct tun_struct {TYPE_1__* pcpu_stats; int /*<<< orphan*/ * tfiles; int /*<<< orphan*/  numqueues; } ;
struct TYPE_4__ {int /*<<< orphan*/  producer_lock; } ;
struct tun_file {TYPE_2__ tx_ring; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_dropped; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 size_t READ_ONCE (int /*<<< orphan*/ ) ; 
 size_t XDP_XMIT_FLAGS_MASK ; 
 size_t XDP_XMIT_FLUSH ; 
 scalar_t__ __ptr_ring_produce (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  __tun_xdp_flush_tfile (struct tun_file*) ; 
 struct tun_struct* netdev_priv (struct net_device*) ; 
 struct tun_file* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 size_t smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 void* tun_xdp_to_ptr (struct xdp_frame*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdp_return_frame_rx_napi (struct xdp_frame*) ; 

__attribute__((used)) static int tun_xdp_xmit(struct net_device *dev, int n,
			struct xdp_frame **frames, u32 flags)
{
	struct tun_struct *tun = netdev_priv(dev);
	struct tun_file *tfile;
	u32 numqueues;
	int drops = 0;
	int cnt = n;
	int i;

	if (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		return -EINVAL;

	rcu_read_lock();

resample:
	numqueues = READ_ONCE(tun->numqueues);
	if (!numqueues) {
		rcu_read_unlock();
		return -ENXIO; /* Caller will free/return all frames */
	}

	tfile = rcu_dereference(tun->tfiles[smp_processor_id() %
					    numqueues]);
	if (unlikely(!tfile))
		goto resample;

	spin_lock(&tfile->tx_ring.producer_lock);
	for (i = 0; i < n; i++) {
		struct xdp_frame *xdp = frames[i];
		/* Encode the XDP flag into lowest bit for consumer to differ
		 * XDP buffer from sk_buff.
		 */
		void *frame = tun_xdp_to_ptr(xdp);

		if (__ptr_ring_produce(&tfile->tx_ring, frame)) {
			this_cpu_inc(tun->pcpu_stats->tx_dropped);
			xdp_return_frame_rx_napi(xdp);
			drops++;
		}
	}
	spin_unlock(&tfile->tx_ring.producer_lock);

	if (flags & XDP_XMIT_FLUSH)
		__tun_xdp_flush_tfile(tfile);

	rcu_read_unlock();
	return cnt - drops;
}
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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct b44 {int istat; int /*<<< orphan*/  lock; int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  B44_IMASK ; 
 int /*<<< orphan*/  B44_ISTAT ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  __b44_disable_ints (struct b44*) ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int br32 (struct b44*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bw32 (struct b44*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct b44* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t b44_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct b44 *bp = netdev_priv(dev);
	u32 istat, imask;
	int handled = 0;

	spin_lock(&bp->lock);

	istat = br32(bp, B44_ISTAT);
	imask = br32(bp, B44_IMASK);

	/* The interrupt mask register controls which interrupt bits
	 * will actually raise an interrupt to the CPU when set by hw/firmware,
	 * but doesn't mask off the bits.
	 */
	istat &= imask;
	if (istat) {
		handled = 1;

		if (unlikely(!netif_running(dev))) {
			netdev_info(dev, "late interrupt\n");
			goto irq_ack;
		}

		if (napi_schedule_prep(&bp->napi)) {
			/* NOTE: These writes are posted by the readback of
			 *       the ISTAT register below.
			 */
			bp->istat = istat;
			__b44_disable_ints(bp);
			__napi_schedule(&bp->napi);
		}

irq_ack:
		bw32(bp, B44_ISTAT, istat);
		br32(bp, B44_ISTAT);
	}
	spin_unlock(&bp->lock);
	return IRQ_RETVAL(handled);
}
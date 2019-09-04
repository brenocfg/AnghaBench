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
typedef  int u64 ;
typedef  int u16 ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff_head {int /*<<< orphan*/  lock; } ;
struct sk_buff {int dummy; } ;
struct mv88e6xxx_port_hwtstamp {int /*<<< orphan*/  port_id; } ;
struct mv88e6xxx_chip {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  tstamp_tc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int MV88E6XXX_PTP_TS_VALID ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  memset (struct skb_shared_hwtstamps*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int mv88e6xxx_port_ptp_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int mv88e6xxx_port_ptp_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mv88e6xxx_ts_valid (int) ; 
 int /*<<< orphan*/  netif_rx_ni (struct sk_buff*) ; 
 int /*<<< orphan*/  ns_to_ktime (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ seq_match (struct sk_buff*,int) ; 
 struct skb_shared_hwtstamps* skb_hwtstamps (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_splice_tail_init (struct sk_buff_head*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int timecounter_cyc2time (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mv88e6xxx_get_rxts(struct mv88e6xxx_chip *chip,
			       struct mv88e6xxx_port_hwtstamp *ps,
			       struct sk_buff *skb, u16 reg,
			       struct sk_buff_head *rxq)
{
	u16 buf[4] = { 0 }, status, seq_id;
	struct skb_shared_hwtstamps *shwt;
	struct sk_buff_head received;
	u64 ns, timelo, timehi;
	unsigned long flags;
	int err;

	/* The latched timestamp belongs to one of the received frames. */
	__skb_queue_head_init(&received);
	spin_lock_irqsave(&rxq->lock, flags);
	skb_queue_splice_tail_init(rxq, &received);
	spin_unlock_irqrestore(&rxq->lock, flags);

	mutex_lock(&chip->reg_lock);
	err = mv88e6xxx_port_ptp_read(chip, ps->port_id,
				      reg, buf, ARRAY_SIZE(buf));
	mutex_unlock(&chip->reg_lock);
	if (err)
		pr_err("failed to get the receive time stamp\n");

	status = buf[0];
	timelo = buf[1];
	timehi = buf[2];
	seq_id = buf[3];

	if (status & MV88E6XXX_PTP_TS_VALID) {
		mutex_lock(&chip->reg_lock);
		err = mv88e6xxx_port_ptp_write(chip, ps->port_id, reg, 0);
		mutex_unlock(&chip->reg_lock);
		if (err)
			pr_err("failed to clear the receive status\n");
	}
	/* Since the device can only handle one time stamp at a time,
	 * we purge any extra frames from the queue.
	 */
	for ( ; skb; skb = __skb_dequeue(&received)) {
		if (mv88e6xxx_ts_valid(status) && seq_match(skb, seq_id)) {
			ns = timehi << 16 | timelo;

			mutex_lock(&chip->reg_lock);
			ns = timecounter_cyc2time(&chip->tstamp_tc, ns);
			mutex_unlock(&chip->reg_lock);
			shwt = skb_hwtstamps(skb);
			memset(shwt, 0, sizeof(*shwt));
			shwt->hwtstamp = ns_to_ktime(ns);
			status &= ~MV88E6XXX_PTP_TS_VALID;
		}
		netif_rx_ni(skb);
	}
}
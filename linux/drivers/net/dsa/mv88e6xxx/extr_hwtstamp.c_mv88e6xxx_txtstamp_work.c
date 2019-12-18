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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {int dummy; } ;
struct mv88e6xxx_ptp_ops {int /*<<< orphan*/  dep_sts_reg; } ;
struct mv88e6xxx_port_hwtstamp {int tx_seq_id; int /*<<< orphan*/  state; struct sk_buff* tx_skb; int /*<<< orphan*/  port_id; scalar_t__ tx_tstamp_start; } ;
struct mv88e6xxx_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  tstamp_tc; TYPE_2__* info; } ;
typedef  int /*<<< orphan*/  shhwtstamps ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {struct mv88e6xxx_ptp_ops* ptp_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  MV88E6XXX_HWTSTAMP_TX_IN_PROGRESS ; 
 int MV88E6XXX_PTP_TS_STATUS_MASK ; 
 int MV88E6XXX_PTP_TS_STATUS_NORMAL ; 
 int MV88E6XXX_PTP_TS_VALID ; 
 scalar_t__ TX_TSTAMP_TIMEOUT ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct skb_shared_hwtstamps*,int /*<<< orphan*/ ,int) ; 
 int mv88e6xxx_port_ptp_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv88e6xxx_port_ptp_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_complete_tx_timestamp (struct sk_buff*,struct skb_shared_hwtstamps*) ; 
 scalar_t__ time_is_before_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  timecounter_cyc2time (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mv88e6xxx_txtstamp_work(struct mv88e6xxx_chip *chip,
				   struct mv88e6xxx_port_hwtstamp *ps)
{
	const struct mv88e6xxx_ptp_ops *ptp_ops = chip->info->ops->ptp_ops;
	struct skb_shared_hwtstamps shhwtstamps;
	u16 departure_block[4], status;
	struct sk_buff *tmp_skb;
	u32 time_raw;
	int err;
	u64 ns;

	if (!ps->tx_skb)
		return 0;

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_port_ptp_read(chip, ps->port_id,
				      ptp_ops->dep_sts_reg,
				      departure_block,
				      ARRAY_SIZE(departure_block));
	mv88e6xxx_reg_unlock(chip);

	if (err)
		goto free_and_clear_skb;

	if (!(departure_block[0] & MV88E6XXX_PTP_TS_VALID)) {
		if (time_is_before_jiffies(ps->tx_tstamp_start +
					   TX_TSTAMP_TIMEOUT)) {
			dev_warn(chip->dev, "p%d: clearing tx timestamp hang\n",
				 ps->port_id);
			goto free_and_clear_skb;
		}
		/* The timestamp should be available quickly, while getting it
		 * is high priority and time bounded to only 10ms. A poll is
		 * warranted so restart the work.
		 */
		return 1;
	}

	/* We have the timestamp; go ahead and clear valid now */
	mv88e6xxx_reg_lock(chip);
	mv88e6xxx_port_ptp_write(chip, ps->port_id, ptp_ops->dep_sts_reg, 0);
	mv88e6xxx_reg_unlock(chip);

	status = departure_block[0] & MV88E6XXX_PTP_TS_STATUS_MASK;
	if (status != MV88E6XXX_PTP_TS_STATUS_NORMAL) {
		dev_warn(chip->dev, "p%d: tx timestamp overrun\n", ps->port_id);
		goto free_and_clear_skb;
	}

	if (departure_block[3] != ps->tx_seq_id) {
		dev_warn(chip->dev, "p%d: unexpected seq. id\n", ps->port_id);
		goto free_and_clear_skb;
	}

	memset(&shhwtstamps, 0, sizeof(shhwtstamps));
	time_raw = ((u32)departure_block[2] << 16) | departure_block[1];
	mv88e6xxx_reg_lock(chip);
	ns = timecounter_cyc2time(&chip->tstamp_tc, time_raw);
	mv88e6xxx_reg_unlock(chip);
	shhwtstamps.hwtstamp = ns_to_ktime(ns);

	dev_dbg(chip->dev,
		"p%d: txtstamp %llx status 0x%04x skb ID 0x%04x hw ID 0x%04x\n",
		ps->port_id, ktime_to_ns(shhwtstamps.hwtstamp),
		departure_block[0], ps->tx_seq_id, departure_block[3]);

	/* skb_complete_tx_timestamp() will free up the client to make
	 * another timestamp-able transmit. We have to be ready for it
	 * -- by clearing the ps->tx_skb "flag" -- beforehand.
	 */

	tmp_skb = ps->tx_skb;
	ps->tx_skb = NULL;
	clear_bit_unlock(MV88E6XXX_HWTSTAMP_TX_IN_PROGRESS, &ps->state);
	skb_complete_tx_timestamp(tmp_skb, &shhwtstamps);

	return 0;

free_and_clear_skb:
	dev_kfree_skb_any(ps->tx_skb);
	ps->tx_skb = NULL;
	clear_bit_unlock(MV88E6XXX_HWTSTAMP_TX_IN_PROGRESS, &ps->state);

	return 0;
}
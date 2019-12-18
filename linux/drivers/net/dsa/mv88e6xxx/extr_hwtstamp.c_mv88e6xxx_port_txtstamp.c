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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct mv88e6xxx_port_hwtstamp {int /*<<< orphan*/  tx_seq_id; int /*<<< orphan*/  tx_tstamp_start; struct sk_buff* tx_skb; int /*<<< orphan*/  state; } ;
struct mv88e6xxx_chip {int /*<<< orphan*/  ptp_clock; struct mv88e6xxx_port_hwtstamp* port_hwtstamp; } ;
struct dsa_switch {struct mv88e6xxx_chip* priv; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int tx_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6XXX_HWTSTAMP_TX_IN_PROGRESS ; 
 int OFF_PTP_SEQUENCE_ID ; 
 int SKBTX_HW_TSTAMP ; 
 int /*<<< orphan*/  be16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/ * mv88e6xxx_should_tstamp (struct mv88e6xxx_chip*,int,struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  ptp_schedule_worker (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ test_and_set_bit_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool mv88e6xxx_port_txtstamp(struct dsa_switch *ds, int port,
			     struct sk_buff *clone, unsigned int type)
{
	struct mv88e6xxx_chip *chip = ds->priv;
	struct mv88e6xxx_port_hwtstamp *ps = &chip->port_hwtstamp[port];
	__be16 *seq_ptr;
	u8 *hdr;

	if (!(skb_shinfo(clone)->tx_flags & SKBTX_HW_TSTAMP))
		return false;

	hdr = mv88e6xxx_should_tstamp(chip, port, clone, type);
	if (!hdr)
		return false;

	seq_ptr = (__be16 *)(hdr + OFF_PTP_SEQUENCE_ID);

	if (test_and_set_bit_lock(MV88E6XXX_HWTSTAMP_TX_IN_PROGRESS,
				  &ps->state))
		return false;

	ps->tx_skb = clone;
	ps->tx_tstamp_start = jiffies;
	ps->tx_seq_id = be16_to_cpup(seq_ptr);

	ptp_schedule_worker(chip->ptp_clock, 0);
	return true;
}
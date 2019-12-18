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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  collisions; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_missed_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; } ;
struct tsi108_prv_data {int /*<<< orphan*/  misclock; int /*<<< orphan*/  tx_pause_drop; TYPE_1__ stats; int /*<<< orphan*/  tx_coll_abort; int /*<<< orphan*/  rx_long_fcs; int /*<<< orphan*/  rx_short_fcs; int /*<<< orphan*/  rx_overruns; int /*<<< orphan*/  rx_underruns; int /*<<< orphan*/  rx_fcs; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSI108_STAT_CARRY1 ; 
 int /*<<< orphan*/  TSI108_STAT_CARRY1_RXALIGN ; 
 int /*<<< orphan*/  TSI108_STAT_CARRY1_RXBYTES ; 
 int /*<<< orphan*/  TSI108_STAT_CARRY1_RXDROP ; 
 int /*<<< orphan*/  TSI108_STAT_CARRY1_RXFCS ; 
 int /*<<< orphan*/  TSI108_STAT_CARRY1_RXFRAG ; 
 int /*<<< orphan*/  TSI108_STAT_CARRY1_RXJABBER ; 
 int /*<<< orphan*/  TSI108_STAT_CARRY1_RXJUMBO ; 
 int /*<<< orphan*/  TSI108_STAT_CARRY1_RXLENGTH ; 
 int /*<<< orphan*/  TSI108_STAT_CARRY1_RXMCAST ; 
 int /*<<< orphan*/  TSI108_STAT_CARRY1_RXPKTS ; 
 int /*<<< orphan*/  TSI108_STAT_CARRY1_RXRUNT ; 
 int /*<<< orphan*/  TSI108_STAT_CARRY2 ; 
 int /*<<< orphan*/  TSI108_STAT_CARRY2_TXBYTES ; 
 int /*<<< orphan*/  TSI108_STAT_CARRY2_TXEXCOL ; 
 int /*<<< orphan*/  TSI108_STAT_CARRY2_TXEXDEF ; 
 int /*<<< orphan*/  TSI108_STAT_CARRY2_TXPAUSE ; 
 int /*<<< orphan*/  TSI108_STAT_CARRY2_TXPKTS ; 
 int /*<<< orphan*/  TSI108_STAT_CARRY2_TXTCOL ; 
 int /*<<< orphan*/  TSI108_STAT_RXALIGN_CARRY ; 
 int /*<<< orphan*/  TSI108_STAT_RXBYTES_CARRY ; 
 int /*<<< orphan*/  TSI108_STAT_RXDROP_CARRY ; 
 int /*<<< orphan*/  TSI108_STAT_RXFCS_CARRY ; 
 int /*<<< orphan*/  TSI108_STAT_RXFRAG_CARRY ; 
 int /*<<< orphan*/  TSI108_STAT_RXJABBER_CARRY ; 
 int /*<<< orphan*/  TSI108_STAT_RXJUMBO_CARRY ; 
 int /*<<< orphan*/  TSI108_STAT_RXLENGTH_CARRY ; 
 int /*<<< orphan*/  TSI108_STAT_RXMCAST_CARRY ; 
 int /*<<< orphan*/  TSI108_STAT_RXPKTS_CARRY ; 
 int /*<<< orphan*/  TSI108_STAT_RXRUNT_CARRY ; 
 int /*<<< orphan*/  TSI108_STAT_TXBYTES_CARRY ; 
 int /*<<< orphan*/  TSI108_STAT_TXEXCOL_CARRY ; 
 int /*<<< orphan*/  TSI108_STAT_TXEXDEF_CARRY ; 
 int /*<<< orphan*/  TSI108_STAT_TXPAUSEDROP_CARRY ; 
 int /*<<< orphan*/  TSI108_STAT_TXPKTS_CARRY ; 
 int /*<<< orphan*/  TSI108_STAT_TXTCOL_CARRY ; 
 int /*<<< orphan*/  TSI_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSI_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tsi108_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tsi108_stat_carry_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tsi108_stat_carry(struct net_device *dev)
{
	struct tsi108_prv_data *data = netdev_priv(dev);
	unsigned long flags;
	u32 carry1, carry2;

	spin_lock_irqsave(&data->misclock, flags);

	carry1 = TSI_READ(TSI108_STAT_CARRY1);
	carry2 = TSI_READ(TSI108_STAT_CARRY2);

	TSI_WRITE(TSI108_STAT_CARRY1, carry1);
	TSI_WRITE(TSI108_STAT_CARRY2, carry2);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXBYTES,
			      TSI108_STAT_RXBYTES_CARRY, &data->stats.rx_bytes);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXPKTS,
			      TSI108_STAT_RXPKTS_CARRY,
			      &data->stats.rx_packets);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXFCS,
			      TSI108_STAT_RXFCS_CARRY, &data->rx_fcs);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXMCAST,
			      TSI108_STAT_RXMCAST_CARRY,
			      &data->stats.multicast);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXALIGN,
			      TSI108_STAT_RXALIGN_CARRY,
			      &data->stats.rx_frame_errors);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXLENGTH,
			      TSI108_STAT_RXLENGTH_CARRY,
			      &data->stats.rx_length_errors);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXRUNT,
			      TSI108_STAT_RXRUNT_CARRY, &data->rx_underruns);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXJUMBO,
			      TSI108_STAT_RXJUMBO_CARRY, &data->rx_overruns);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXFRAG,
			      TSI108_STAT_RXFRAG_CARRY, &data->rx_short_fcs);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXJABBER,
			      TSI108_STAT_RXJABBER_CARRY, &data->rx_long_fcs);

	tsi108_stat_carry_one(carry1, TSI108_STAT_CARRY1_RXDROP,
			      TSI108_STAT_RXDROP_CARRY,
			      &data->stats.rx_missed_errors);

	tsi108_stat_carry_one(carry2, TSI108_STAT_CARRY2_TXBYTES,
			      TSI108_STAT_TXBYTES_CARRY, &data->stats.tx_bytes);

	tsi108_stat_carry_one(carry2, TSI108_STAT_CARRY2_TXPKTS,
			      TSI108_STAT_TXPKTS_CARRY,
			      &data->stats.tx_packets);

	tsi108_stat_carry_one(carry2, TSI108_STAT_CARRY2_TXEXDEF,
			      TSI108_STAT_TXEXDEF_CARRY,
			      &data->stats.tx_aborted_errors);

	tsi108_stat_carry_one(carry2, TSI108_STAT_CARRY2_TXEXCOL,
			      TSI108_STAT_TXEXCOL_CARRY, &data->tx_coll_abort);

	tsi108_stat_carry_one(carry2, TSI108_STAT_CARRY2_TXTCOL,
			      TSI108_STAT_TXTCOL_CARRY,
			      &data->stats.collisions);

	tsi108_stat_carry_one(carry2, TSI108_STAT_CARRY2_TXPAUSE,
			      TSI108_STAT_TXPAUSEDROP_CARRY,
			      &data->tx_pause_drop);

	spin_unlock_irqrestore(&data->misclock, flags);
}
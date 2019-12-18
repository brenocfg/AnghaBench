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
struct mt76_tx_status {int valid; int success; int aggr; int ack_req; void* rate; void* wcid; void* pktid; } ;
struct mt7601u_dev {int dummy; } ;

/* Variables and functions */
 void* FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_TX_STAT_FIFO ; 
 int MT_TX_STAT_FIFO_ACKREQ ; 
 int MT_TX_STAT_FIFO_AGGR ; 
 int /*<<< orphan*/  MT_TX_STAT_FIFO_PID_TYPE ; 
 int /*<<< orphan*/  MT_TX_STAT_FIFO_RATE ; 
 int MT_TX_STAT_FIFO_SUCCESS ; 
 int MT_TX_STAT_FIFO_VALID ; 
 int /*<<< orphan*/  MT_TX_STAT_FIFO_WCID ; 
 int mt7601u_rr (struct mt7601u_dev*,int /*<<< orphan*/ ) ; 

struct mt76_tx_status mt7601u_mac_fetch_tx_status(struct mt7601u_dev *dev)
{
	struct mt76_tx_status stat = {};
	u32 val;

	val = mt7601u_rr(dev, MT_TX_STAT_FIFO);
	stat.valid = !!(val & MT_TX_STAT_FIFO_VALID);
	stat.success = !!(val & MT_TX_STAT_FIFO_SUCCESS);
	stat.aggr = !!(val & MT_TX_STAT_FIFO_AGGR);
	stat.ack_req = !!(val & MT_TX_STAT_FIFO_ACKREQ);
	stat.pktid = FIELD_GET(MT_TX_STAT_FIFO_PID_TYPE, val);
	stat.wcid = FIELD_GET(MT_TX_STAT_FIFO_WCID, val);
	stat.rate = FIELD_GET(MT_TX_STAT_FIFO_RATE, val);

	return stat;
}
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
typedef  int ulong ;
typedef  int u32 ;
struct smsc911x_data {TYPE_1__* ops; } ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* tx_writefifo ) (struct smsc911x_data*,unsigned int*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FIFO_INT ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  SMSC_WARN (struct smsc911x_data*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int TX_CMD_A_FIRST_SEG_ ; 
 unsigned int TX_CMD_A_LAST_SEG_ ; 
 int /*<<< orphan*/  TX_DATA_FIFO ; 
 int /*<<< orphan*/  TX_FIFO_INF ; 
 unsigned int TX_FIFO_INF_TDFREE_ ; 
 unsigned int TX_FIFO_LOW_THRESHOLD ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 struct smsc911x_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 unsigned int smsc911x_reg_read (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc911x_reg_write (struct smsc911x_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int smsc911x_tx_get_txstatcount (struct smsc911x_data*) ; 
 int /*<<< orphan*/  smsc911x_tx_update_txcounters (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct smsc911x_data*,unsigned int*,int) ; 
 int /*<<< orphan*/  tx_err ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static netdev_tx_t
smsc911x_hard_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct smsc911x_data *pdata = netdev_priv(dev);
	unsigned int freespace;
	unsigned int tx_cmd_a;
	unsigned int tx_cmd_b;
	unsigned int temp;
	u32 wrsz;
	ulong bufp;

	freespace = smsc911x_reg_read(pdata, TX_FIFO_INF) & TX_FIFO_INF_TDFREE_;

	if (unlikely(freespace < TX_FIFO_LOW_THRESHOLD))
		SMSC_WARN(pdata, tx_err,
			  "Tx data fifo low, space available: %d", freespace);

	/* Word alignment adjustment */
	tx_cmd_a = (u32)((ulong)skb->data & 0x03) << 16;
	tx_cmd_a |= TX_CMD_A_FIRST_SEG_ | TX_CMD_A_LAST_SEG_;
	tx_cmd_a |= (unsigned int)skb->len;

	tx_cmd_b = ((unsigned int)skb->len) << 16;
	tx_cmd_b |= (unsigned int)skb->len;

	smsc911x_reg_write(pdata, TX_DATA_FIFO, tx_cmd_a);
	smsc911x_reg_write(pdata, TX_DATA_FIFO, tx_cmd_b);

	bufp = (ulong)skb->data & (~0x3);
	wrsz = (u32)skb->len + 3;
	wrsz += (u32)((ulong)skb->data & 0x3);
	wrsz >>= 2;

	pdata->ops->tx_writefifo(pdata, (unsigned int *)bufp, wrsz);
	freespace -= (skb->len + 32);
	skb_tx_timestamp(skb);
	dev_consume_skb_any(skb);

	if (unlikely(smsc911x_tx_get_txstatcount(pdata) >= 30))
		smsc911x_tx_update_txcounters(dev);

	if (freespace < TX_FIFO_LOW_THRESHOLD) {
		netif_stop_queue(dev);
		temp = smsc911x_reg_read(pdata, FIFO_INT);
		temp &= 0x00FFFFFF;
		temp |= 0x32000000;
		smsc911x_reg_write(pdata, FIFO_INT, temp);
	}

	return NETDEV_TX_OK;
}
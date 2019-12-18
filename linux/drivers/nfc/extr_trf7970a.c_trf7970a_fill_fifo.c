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
typedef  unsigned int u8 ;
struct trf7970a {int /*<<< orphan*/  timeout_work; int /*<<< orphan*/  dev; struct sk_buff* tx_skb; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  prefix ;

/* Variables and functions */
 unsigned int TRF7970A_CMD_BIT_CONTINUOUS ; 
 unsigned int TRF7970A_FIFO_IO_REGISTER ; 
 unsigned int TRF7970A_FIFO_SIZE ; 
 int /*<<< orphan*/  TRF7970A_FIFO_STATUS ; 
 unsigned int TRF7970A_FIFO_STATUS_OVERFLOW ; 
 int /*<<< orphan*/  TRF7970A_WAIT_FOR_FIFO_DRAIN_TIMEOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int min (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int trf7970a_read (struct trf7970a*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  trf7970a_send_err_upstream (struct trf7970a*,int) ; 
 int trf7970a_transmit (struct trf7970a*,struct sk_buff*,unsigned int,unsigned int*,int) ; 

__attribute__((used)) static void trf7970a_fill_fifo(struct trf7970a *trf)
{
	struct sk_buff *skb = trf->tx_skb;
	unsigned int len;
	int ret;
	u8 fifo_bytes;
	u8 prefix;

	ret = trf7970a_read(trf, TRF7970A_FIFO_STATUS, &fifo_bytes);
	if (ret) {
		trf7970a_send_err_upstream(trf, ret);
		return;
	}

	dev_dbg(trf->dev, "Filling FIFO - fifo_bytes: 0x%x\n", fifo_bytes);

	fifo_bytes &= ~TRF7970A_FIFO_STATUS_OVERFLOW;

	/* Calculate how much more data can be written to the fifo */
	len = TRF7970A_FIFO_SIZE - fifo_bytes;
	if (!len) {
		schedule_delayed_work(&trf->timeout_work,
			msecs_to_jiffies(TRF7970A_WAIT_FOR_FIFO_DRAIN_TIMEOUT));
		return;
	}

	len = min(skb->len, len);

	prefix = TRF7970A_CMD_BIT_CONTINUOUS | TRF7970A_FIFO_IO_REGISTER;

	ret = trf7970a_transmit(trf, skb, len, &prefix, sizeof(prefix));
	if (ret)
		trf7970a_send_err_upstream(trf, ret);
}
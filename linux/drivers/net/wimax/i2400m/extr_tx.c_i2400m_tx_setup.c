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
struct i2400m {scalar_t__ bus_tx_block_size; int /*<<< orphan*/  tx_lock; void* tx_buf; int /*<<< orphan*/ * tx_msg; scalar_t__ tx_msg_size; scalar_t__ tx_out; scalar_t__ tx_in; scalar_t__ tx_sequence; int /*<<< orphan*/  wake_tx_ws; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int I2400M_TX_BUF_SIZE ; 
 int I2400M_TX_MSG_SIZE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2400m_wake_tx_work ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int i2400m_tx_setup(struct i2400m *i2400m)
{
	int result = 0;
	void *tx_buf;
	unsigned long flags;

	/* Do this here only once -- can't do on
	 * i2400m_hard_start_xmit() as we'll cause race conditions if
	 * the WS was scheduled on another CPU */
	INIT_WORK(&i2400m->wake_tx_ws, i2400m_wake_tx_work);

	tx_buf = kmalloc(I2400M_TX_BUF_SIZE, GFP_ATOMIC);
	if (tx_buf == NULL) {
		result = -ENOMEM;
		goto error_kmalloc;
	}

	/*
	 * Fail the build if we can't fit at least two maximum size messages
	 * on the TX FIFO [one being delivered while one is constructed].
	 */
	BUILD_BUG_ON(2 * I2400M_TX_MSG_SIZE > I2400M_TX_BUF_SIZE);
	spin_lock_irqsave(&i2400m->tx_lock, flags);
	i2400m->tx_sequence = 0;
	i2400m->tx_in = 0;
	i2400m->tx_out = 0;
	i2400m->tx_msg_size = 0;
	i2400m->tx_msg = NULL;
	i2400m->tx_buf = tx_buf;
	spin_unlock_irqrestore(&i2400m->tx_lock, flags);
	/* Huh? the bus layer has to define this... */
	BUG_ON(i2400m->bus_tx_block_size == 0);
error_kmalloc:
	return result;

}
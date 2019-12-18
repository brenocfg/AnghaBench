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
struct tty_struct {int /*<<< orphan*/  hw_stopped; int /*<<< orphan*/  stopped; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct fwtty_transaction {TYPE_2__ dma_pended; } ;
struct TYPE_3__ {int /*<<< orphan*/  sent; int /*<<< orphan*/  txns; int /*<<< orphan*/  fifo_errs; int /*<<< orphan*/  tx_stall; } ;
struct fwtty_port {int /*<<< orphan*/  wait_tx; int /*<<< orphan*/  flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_fifo; int /*<<< orphan*/  drain; TYPE_1__ stats; int /*<<< orphan*/  peer; int /*<<< orphan*/  port; } ;
struct fwtty_peer {int /*<<< orphan*/  fifo_addr; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EALREADY ; 
 int EIO ; 
 int ENODATA ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HZ ; 
 int /*<<< orphan*/  IN_TX ; 
 int /*<<< orphan*/  STOP_TX ; 
 int /*<<< orphan*/  TCODE_WRITE_BLOCK_REQUEST ; 
 int WAKEUP_CHARS ; 
 int WRITER_MINIMUM ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dma_fifo_level (int /*<<< orphan*/ *) ; 
 int dma_fifo_out_level (int /*<<< orphan*/ *) ; 
 int dma_fifo_out_pend (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  fwtty_dbg (struct fwtty_port*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fwtty_err_ratelimited (struct fwtty_port*,char*,int) ; 
 int /*<<< orphan*/  fwtty_profile_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwtty_send_txn_async (struct fwtty_peer*,struct fwtty_transaction*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fwtty_port*) ; 
 int /*<<< orphan*/  fwtty_tx_complete ; 
 int /*<<< orphan*/  fwtty_txn_cache ; 
 struct fwtty_transaction* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct fwtty_transaction*) ; 
 struct fwtty_peer* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fwtty_tx(struct fwtty_port *port, bool drain)
{
	struct fwtty_peer *peer;
	struct fwtty_transaction *txn;
	struct tty_struct *tty;
	int n, len;

	tty = tty_port_tty_get(&port->port);
	if (!tty)
		return -ENOENT;

	rcu_read_lock();
	peer = rcu_dereference(port->peer);
	if (!peer) {
		n = -EIO;
		goto out;
	}

	if (test_and_set_bit(IN_TX, &port->flags)) {
		n = -EALREADY;
		goto out;
	}

	/* try to write as many dma transactions out as possible */
	n = -EAGAIN;
	while (!tty->stopped && !tty->hw_stopped &&
	       !test_bit(STOP_TX, &port->flags)) {
		txn = kmem_cache_alloc(fwtty_txn_cache, GFP_ATOMIC);
		if (!txn) {
			n = -ENOMEM;
			break;
		}

		spin_lock_bh(&port->lock);
		n = dma_fifo_out_pend(&port->tx_fifo, &txn->dma_pended);
		spin_unlock_bh(&port->lock);

		fwtty_dbg(port, "out: %u rem: %d\n", txn->dma_pended.len, n);

		if (n < 0) {
			kmem_cache_free(fwtty_txn_cache, txn);
			if (n == -EAGAIN) {
				++port->stats.tx_stall;
			} else if (n == -ENODATA) {
				fwtty_profile_data(port->stats.txns, 0);
			} else {
				++port->stats.fifo_errs;
				fwtty_err_ratelimited(port, "fifo err: %d\n",
						      n);
			}
			break;
		}

		fwtty_profile_data(port->stats.txns, txn->dma_pended.len);

		fwtty_send_txn_async(peer, txn, TCODE_WRITE_BLOCK_REQUEST,
				     peer->fifo_addr, txn->dma_pended.data,
				     txn->dma_pended.len, fwtty_tx_complete,
				     port);
		++port->stats.sent;

		/*
		 * Stop tx if the 'last view' of the fifo is empty or if
		 * this is the writer and there's not enough data to bother
		 */
		if (n == 0 || (!drain && n < WRITER_MINIMUM))
			break;
	}

	if (n >= 0 || n == -EAGAIN || n == -ENOMEM || n == -ENODATA) {
		spin_lock_bh(&port->lock);
		len = dma_fifo_out_level(&port->tx_fifo);
		if (len) {
			unsigned long delay = (n == -ENOMEM) ? HZ : 1;

			schedule_delayed_work(&port->drain, delay);
		}
		len = dma_fifo_level(&port->tx_fifo);
		spin_unlock_bh(&port->lock);

		/* wakeup the writer */
		if (drain && len < WAKEUP_CHARS)
			tty_wakeup(tty);
	}

	clear_bit(IN_TX, &port->flags);
	wake_up_interruptible(&port->wait_tx);

out:
	rcu_read_unlock();
	tty_kref_put(tty);
	return n;
}
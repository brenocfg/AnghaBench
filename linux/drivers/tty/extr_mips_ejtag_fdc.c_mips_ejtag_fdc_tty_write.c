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
struct tty_struct {struct mips_ejtag_fdc_tty_port* driver_data; } ;
struct TYPE_2__ {scalar_t__ xmit_buf; } ;
struct mips_ejtag_fdc_tty_port {int xmit_cnt; scalar_t__ xmit_head; int /*<<< orphan*/  xmit_lock; int /*<<< orphan*/  xmit_empty; TYPE_1__ port; struct mips_ejtag_fdc_tty* driver; } ;
struct mips_ejtag_fdc_tty {scalar_t__ xmit_size; int /*<<< orphan*/  waitqueue; int /*<<< orphan*/  xmit_total; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char const*,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mips_ejtag_fdc_tty_write(struct tty_struct *tty,
				    const unsigned char *buf, int total)
{
	int count, block;
	struct mips_ejtag_fdc_tty_port *dport = tty->driver_data;
	struct mips_ejtag_fdc_tty *priv = dport->driver;

	/*
	 * Write to output buffer.
	 *
	 * The reason that we asynchronously write the buffer is because if we
	 * were to write the buffer synchronously then because the channels are
	 * per-CPU the buffer would be written to the channel of whatever CPU
	 * we're running on.
	 *
	 * What we actually want to happen is have all input and output done on
	 * one CPU.
	 */
	spin_lock(&dport->xmit_lock);
	/* Work out how many bytes we can write to the xmit buffer */
	total = min(total, (int)(priv->xmit_size - dport->xmit_cnt));
	atomic_add(total, &priv->xmit_total);
	dport->xmit_cnt += total;
	/* Write the actual bytes (may need splitting if it wraps) */
	for (count = total; count; count -= block) {
		block = min(count, (int)(priv->xmit_size - dport->xmit_head));
		memcpy(dport->port.xmit_buf + dport->xmit_head, buf, block);
		dport->xmit_head += block;
		if (dport->xmit_head >= priv->xmit_size)
			dport->xmit_head -= priv->xmit_size;
		buf += block;
	}
	count = dport->xmit_cnt;
	/* Xmit buffer no longer empty? */
	if (count)
		reinit_completion(&dport->xmit_empty);
	spin_unlock(&dport->xmit_lock);

	/* Wake up the kthread */
	if (total)
		wake_up_interruptible(&priv->waitqueue);
	return total;
}
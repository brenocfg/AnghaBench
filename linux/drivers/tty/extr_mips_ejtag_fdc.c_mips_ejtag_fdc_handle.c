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
struct mips_ejtag_fdc_tty_port {int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  port; int /*<<< orphan*/  rx_buf; } ;
struct mips_ejtag_fdc_tty {int sysrq_pressed; int xmit_full; int /*<<< orphan*/  lock; int /*<<< orphan*/  waitqueue; int /*<<< orphan*/  driver_name; int /*<<< orphan*/  dev; struct mips_ejtag_fdc_tty_port* ports; } ;
struct TYPE_3__ {unsigned int index; } ;
struct TYPE_4__ {TYPE_1__ cons; } ;

/* Variables and functions */
 unsigned int CONFIG_MIPS_EJTAG_FDC_KGDB_CHAN ; 
 int /*<<< orphan*/  REG_FDCFG ; 
 unsigned int REG_FDCFG_TXINTTHRES ; 
 unsigned int REG_FDCFG_TXINTTHRES_DISABLED ; 
 int /*<<< orphan*/  REG_FDRX ; 
 int /*<<< orphan*/  REG_FDSTAT ; 
 unsigned int REG_FDSTAT_RXCHAN ; 
 unsigned int REG_FDSTAT_RXCHAN_SHIFT ; 
 unsigned int REG_FDSTAT_RXE ; 
 unsigned int REG_FDSTAT_TXF ; 
 int /*<<< orphan*/  TTY_NORMAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,unsigned int,int,char*) ; 
 int /*<<< orphan*/  handle_sysrq (char) ; 
 TYPE_2__ mips_ejtag_fdc_con ; 
 int mips_ejtag_fdc_decode (unsigned int,char*) ; 
 unsigned int mips_ejtag_fdc_read (struct mips_ejtag_fdc_tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_ejtag_fdc_write (struct mips_ejtag_fdc_tty*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 scalar_t__ tty_insert_flip_char (int /*<<< orphan*/ *,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mips_ejtag_fdc_handle(struct mips_ejtag_fdc_tty *priv)
{
	struct mips_ejtag_fdc_tty_port *dport;
	unsigned int stat, channel, data, cfg, i, flipped;
	int len;
	char buf[4];

	for (;;) {
		/* Find which channel the next FDC word is destined for */
		stat = mips_ejtag_fdc_read(priv, REG_FDSTAT);
		if (stat & REG_FDSTAT_RXE)
			break;
		channel = (stat & REG_FDSTAT_RXCHAN) >> REG_FDSTAT_RXCHAN_SHIFT;
		dport = &priv->ports[channel];

		/* Read out the FDC word, decode it, and pass to tty layer */
		raw_spin_lock(&dport->rx_lock);
		data = mips_ejtag_fdc_read(priv, REG_FDRX);

		len = mips_ejtag_fdc_decode(data, buf);
		dev_dbg(priv->dev, "%s%u: in  %08x: \"%*pE\"\n",
			priv->driver_name, channel, data, len, buf);

		flipped = 0;
		for (i = 0; i < len; ++i) {
#ifdef CONFIG_MAGIC_SYSRQ
#ifdef CONFIG_MIPS_EJTAG_FDC_KGDB
			/* Support just Ctrl+C with KGDB channel */
			if (channel == CONFIG_MIPS_EJTAG_FDC_KGDB_CHAN) {
				if (buf[i] == '\x03') { /* ^C */
					handle_sysrq('g');
					continue;
				}
			}
#endif
			/* Support Ctrl+O for console channel */
			if (channel == mips_ejtag_fdc_con.cons.index) {
				if (buf[i] == '\x0f') {	/* ^O */
					priv->sysrq_pressed =
						!priv->sysrq_pressed;
					if (priv->sysrq_pressed)
						continue;
				} else if (priv->sysrq_pressed) {
					handle_sysrq(buf[i]);
					priv->sysrq_pressed = false;
					continue;
				}
			}
#endif /* CONFIG_MAGIC_SYSRQ */

			/* Check the port isn't being shut down */
			if (!dport->rx_buf)
				continue;

			flipped += tty_insert_flip_char(&dport->port, buf[i],
							TTY_NORMAL);
		}
		if (flipped)
			tty_flip_buffer_push(&dport->port);

		raw_spin_unlock(&dport->rx_lock);
	}

	/* If TX FIFO no longer full we may be able to write more data */
	raw_spin_lock(&priv->lock);
	if (priv->xmit_full && !(stat & REG_FDSTAT_TXF)) {
		priv->xmit_full = false;

		/* Disable TX interrupt */
		cfg = mips_ejtag_fdc_read(priv, REG_FDCFG);
		cfg &= ~REG_FDCFG_TXINTTHRES;
		cfg |= REG_FDCFG_TXINTTHRES_DISABLED;
		mips_ejtag_fdc_write(priv, REG_FDCFG, cfg);

		/* Wait the kthread so it can try writing more data */
		wake_up_interruptible(&priv->waitqueue);
	}
	raw_spin_unlock(&priv->lock);
}
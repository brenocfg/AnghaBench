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
struct TYPE_2__ {int flags; } ;
struct smsc911x_data {int /*<<< orphan*/  dev_lock; TYPE_1__ config; scalar_t__ ioaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int SMSC911X_SWAP_FIFO ; 
 int SMSC911X_USE_16BIT ; 
 int SMSC911X_USE_32BIT ; 
 int /*<<< orphan*/  TX_DATA_FIFO ; 
 int /*<<< orphan*/  __smsc911x_reg_write_shift (struct smsc911x_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __smsc_shift (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32_rep (scalar_t__,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  swab32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
smsc911x_tx_writefifo_shift(struct smsc911x_data *pdata, unsigned int *buf,
		      unsigned int wordcount)
{
	unsigned long flags;

	spin_lock_irqsave(&pdata->dev_lock, flags);

	if (pdata->config.flags & SMSC911X_SWAP_FIFO) {
		while (wordcount--)
			__smsc911x_reg_write_shift(pdata, TX_DATA_FIFO,
					     swab32(*buf++));
		goto out;
	}

	if (pdata->config.flags & SMSC911X_USE_32BIT) {
		iowrite32_rep(pdata->ioaddr + __smsc_shift(pdata,
						TX_DATA_FIFO), buf, wordcount);
		goto out;
	}

	if (pdata->config.flags & SMSC911X_USE_16BIT) {
		while (wordcount--)
			__smsc911x_reg_write_shift(pdata,
						 TX_DATA_FIFO, *buf++);
		goto out;
	}

	BUG();
out:
	spin_unlock_irqrestore(&pdata->dev_lock, flags);
}
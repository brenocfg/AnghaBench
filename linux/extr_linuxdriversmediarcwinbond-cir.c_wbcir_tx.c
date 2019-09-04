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
struct wbcir_data {scalar_t__ txstate; unsigned int* txbuf; unsigned int txlen; int /*<<< orphan*/  spinlock; scalar_t__ txoff; } ;
struct rc_dev {struct wbcir_data* priv; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (unsigned int,int) ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WBCIR_TXSTATE_INACTIVE ; 
 int /*<<< orphan*/  kfree (unsigned int*) ; 
 unsigned int* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wbcir_irq_tx (struct wbcir_data*) ; 

__attribute__((used)) static int
wbcir_tx(struct rc_dev *dev, unsigned *b, unsigned count)
{
	struct wbcir_data *data = dev->priv;
	unsigned *buf;
	unsigned i;
	unsigned long flags;

	buf = kmalloc_array(count, sizeof(*b), GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	/* Convert values to multiples of 10us */
	for (i = 0; i < count; i++)
		buf[i] = DIV_ROUND_CLOSEST(b[i], 10);

	/* Not sure if this is possible, but better safe than sorry */
	spin_lock_irqsave(&data->spinlock, flags);
	if (data->txstate != WBCIR_TXSTATE_INACTIVE) {
		spin_unlock_irqrestore(&data->spinlock, flags);
		kfree(buf);
		return -EBUSY;
	}

	/* Fill the TX fifo once, the irq handler will do the rest */
	data->txbuf = buf;
	data->txlen = count;
	data->txoff = 0;
	wbcir_irq_tx(data);

	/* We're done */
	spin_unlock_irqrestore(&data->spinlock, flags);
	return count;
}
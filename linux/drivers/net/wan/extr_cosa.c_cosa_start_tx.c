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
struct cosa_data {int /*<<< orphan*/  txbitmap; int /*<<< orphan*/  lock; int /*<<< orphan*/  num; } ;
struct channel_data {char* txbuf; int txsize; int /*<<< orphan*/  num; struct cosa_data* cosa; } ;

/* Variables and functions */
 int COSA_MTU ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_driver_status (struct cosa_data*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cosa_start_tx(struct channel_data *chan, char *buf, int len)
{
	struct cosa_data *cosa = chan->cosa;
	unsigned long flags;
#ifdef DEBUG_DATA
	int i;

	pr_info("cosa%dc%d: starting tx(0x%x)",
		chan->cosa->num, chan->num, len);
	for (i=0; i<len; i++)
		pr_cont(" %02x", buf[i]&0xff);
	pr_cont("\n");
#endif
	spin_lock_irqsave(&cosa->lock, flags);
	chan->txbuf = buf;
	chan->txsize = len;
	if (len > COSA_MTU)
		chan->txsize = COSA_MTU;
	spin_unlock_irqrestore(&cosa->lock, flags);

	/* Tell the firmware we are ready */
	set_bit(chan->num, &cosa->txbitmap);
	put_driver_status(cosa);

	return 0;
}
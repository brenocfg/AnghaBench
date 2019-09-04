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
struct TYPE_2__ {scalar_t__ ToPcChannel; scalar_t__ ToPcSize; int ToPcBuf; int ToHyInt; int ToPcInt; scalar_t__ ToPcFlag; } ;
typedef  TYPE_1__ tErgDpram ;
struct HYSDN_CARD {int debug_flags; int irq_enabled; int myid; int /*<<< orphan*/  state; int /*<<< orphan*/  hysdn_lock; scalar_t__ iobase; TYPE_1__* dpram; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_STATE_BOOTERR ; 
 int /*<<< orphan*/  CARD_STATE_RUN ; 
 scalar_t__ CHAN_SYSTEM ; 
 int ERR_POF_TIMEOUT ; 
 scalar_t__ EvalSysrTokData (struct HYSDN_CARD*,int,int) ; 
 int LOG_POF_CARD ; 
 int LOG_POF_RECORD ; 
 scalar_t__ MAX_RDY_MSG_SIZE ; 
 scalar_t__ MIN_RDY_MSG_SIZE ; 
 scalar_t__ PCI9050_INTR_REG ; 
 int PCI9050_INTR_REG_EN1 ; 
 int PCI9050_INTR_REG_ENPCI ; 
 unsigned long RDY_MAGIC ; 
 int RDY_MAGIC_SIZE ; 
 int bytein (scalar_t__) ; 
 int /*<<< orphan*/  byteout (scalar_t__,int) ; 
 int /*<<< orphan*/  ergo_stopcard (struct HYSDN_CARD*) ; 
 int hynet_enable ; 
 int /*<<< orphan*/  hysdn_addlog (struct HYSDN_CARD*,char*) ; 
 int hysdn_net_create (struct HYSDN_CARD*) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
ergo_waitpofready(struct HYSDN_CARD *card)
{
	tErgDpram *dpr = card->dpram;	/* pointer to DPRAM structure */
	int timecnt = 10000 / 50;	/* timeout is 10 secs max. */
	unsigned long flags;
	int msg_size;
	int i;

	if (card->debug_flags & LOG_POF_CARD)
		hysdn_addlog(card, "ERGO: waiting for pof ready");
	while (timecnt--) {
		/* wait until timeout  */

		if (dpr->ToPcFlag) {
			/* data has arrived */

			if ((dpr->ToPcChannel != CHAN_SYSTEM) ||
			    (dpr->ToPcSize < MIN_RDY_MSG_SIZE) ||
			    (dpr->ToPcSize > MAX_RDY_MSG_SIZE) ||
			    ((*(unsigned long *) dpr->ToPcBuf) != RDY_MAGIC))
				break;	/* an error occurred */

			/* Check for additional data delivered during SysReady */
			msg_size = dpr->ToPcSize - RDY_MAGIC_SIZE;
			if (msg_size > 0)
				if (EvalSysrTokData(card, dpr->ToPcBuf + RDY_MAGIC_SIZE, msg_size))
					break;

			if (card->debug_flags & LOG_POF_RECORD)
				hysdn_addlog(card, "ERGO: pof boot success");
			spin_lock_irqsave(&card->hysdn_lock, flags);

			card->state = CARD_STATE_RUN;	/* now card is running */
			/* enable the cards interrupt */
			byteout(card->iobase + PCI9050_INTR_REG,
				bytein(card->iobase + PCI9050_INTR_REG) |
				(PCI9050_INTR_REG_ENPCI | PCI9050_INTR_REG_EN1));
			card->irq_enabled = 1;	/* we are ready to receive interrupts */

			dpr->ToPcFlag = 0;	/* reset data indicator */
			dpr->ToHyInt = 1;
			dpr->ToPcInt = 1;	/* interrupt to E1 for all cards */

			spin_unlock_irqrestore(&card->hysdn_lock, flags);
			if ((hynet_enable & (1 << card->myid))
			    && (i = hysdn_net_create(card)))
			{
				ergo_stopcard(card);
				card->state = CARD_STATE_BOOTERR;
				return (i);
			}
#ifdef CONFIG_HYSDN_CAPI
			if ((i = hycapi_capi_create(card))) {
				printk(KERN_WARNING "HYSDN: failed to create capi-interface.\n");
			}
#endif /* CONFIG_HYSDN_CAPI */
			return (0);	/* success */
		}		/* data has arrived */
		msleep_interruptible(50);		/* Timeout 50ms */
	}			/* wait until timeout */

	if (card->debug_flags & LOG_POF_CARD)
		hysdn_addlog(card, "ERGO: pof boot ready timeout");
	return (-ERR_POF_TIMEOUT);
}
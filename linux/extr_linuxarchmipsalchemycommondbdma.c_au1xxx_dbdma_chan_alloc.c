#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int dev_flags; scalar_t__ dev_intpolarity; scalar_t__ dev_intlevel; } ;
typedef  TYPE_1__ dbdev_tab_t ;
struct TYPE_9__ {int chan_index; void (* chan_callback ) (int,void*) ;void* chan_callparam; TYPE_1__* chan_dest; TYPE_1__* chan_src; TYPE_3__* chan_ptr; } ;
typedef  TYPE_2__ chan_tab_t ;
struct TYPE_10__ {int ddma_cfg; } ;
typedef  TYPE_3__ au1x_dma_chan_t ;

/* Variables and functions */
 int /*<<< orphan*/  AU1550_DBDMA_PHYS_ADDR ; 
 int DDMA_CFG_DED ; 
 int DDMA_CFG_DP ; 
 int DDMA_CFG_SED ; 
 int DDMA_CFG_SP ; 
 int DDMA_CFG_SYNC ; 
 int DEV_FLAGS_ANYUSE ; 
 int DEV_FLAGS_INUSE ; 
 int DEV_FLAGS_SYNC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int KSEG1ADDR (int /*<<< orphan*/ ) ; 
 int NUM_DBDMA_CHANS ; 
 int /*<<< orphan*/  au1xxx_dbdma_spin_lock ; 
 TYPE_2__** chan_tab_ptr ; 
 int /*<<< orphan*/  dbdma_initialized ; 
 TYPE_1__* find_dbdev_id (int) ; 
 TYPE_2__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 

u32 au1xxx_dbdma_chan_alloc(u32 srcid, u32 destid,
       void (*callback)(int, void *), void *callparam)
{
	unsigned long	flags;
	u32		used, chan;
	u32		dcp;
	int		i;
	dbdev_tab_t	*stp, *dtp;
	chan_tab_t	*ctp;
	au1x_dma_chan_t *cp;

	/*
	 * We do the initialization on the first channel allocation.
	 * We have to wait because of the interrupt handler initialization
	 * which can't be done successfully during board set up.
	 */
	if (!dbdma_initialized)
		return 0;

	stp = find_dbdev_id(srcid);
	if (stp == NULL)
		return 0;
	dtp = find_dbdev_id(destid);
	if (dtp == NULL)
		return 0;

	used = 0;

	/* Check to see if we can get both channels. */
	spin_lock_irqsave(&au1xxx_dbdma_spin_lock, flags);
	if (!(stp->dev_flags & DEV_FLAGS_INUSE) ||
	     (stp->dev_flags & DEV_FLAGS_ANYUSE)) {
		/* Got source */
		stp->dev_flags |= DEV_FLAGS_INUSE;
		if (!(dtp->dev_flags & DEV_FLAGS_INUSE) ||
		     (dtp->dev_flags & DEV_FLAGS_ANYUSE)) {
			/* Got destination */
			dtp->dev_flags |= DEV_FLAGS_INUSE;
		} else {
			/* Can't get dest.  Release src. */
			stp->dev_flags &= ~DEV_FLAGS_INUSE;
			used++;
		}
	} else
		used++;
	spin_unlock_irqrestore(&au1xxx_dbdma_spin_lock, flags);

	if (used)
		return 0;

	/* Let's see if we can allocate a channel for it. */
	ctp = NULL;
	chan = 0;
	spin_lock_irqsave(&au1xxx_dbdma_spin_lock, flags);
	for (i = 0; i < NUM_DBDMA_CHANS; i++)
		if (chan_tab_ptr[i] == NULL) {
			/*
			 * If kmalloc fails, it is caught below same
			 * as a channel not available.
			 */
			ctp = kmalloc(sizeof(chan_tab_t), GFP_ATOMIC);
			chan_tab_ptr[i] = ctp;
			break;
		}
	spin_unlock_irqrestore(&au1xxx_dbdma_spin_lock, flags);

	if (ctp != NULL) {
		memset(ctp, 0, sizeof(chan_tab_t));
		ctp->chan_index = chan = i;
		dcp = KSEG1ADDR(AU1550_DBDMA_PHYS_ADDR);
		dcp += (0x0100 * chan);
		ctp->chan_ptr = (au1x_dma_chan_t *)dcp;
		cp = (au1x_dma_chan_t *)dcp;
		ctp->chan_src = stp;
		ctp->chan_dest = dtp;
		ctp->chan_callback = callback;
		ctp->chan_callparam = callparam;

		/* Initialize channel configuration. */
		i = 0;
		if (stp->dev_intlevel)
			i |= DDMA_CFG_SED;
		if (stp->dev_intpolarity)
			i |= DDMA_CFG_SP;
		if (dtp->dev_intlevel)
			i |= DDMA_CFG_DED;
		if (dtp->dev_intpolarity)
			i |= DDMA_CFG_DP;
		if ((stp->dev_flags & DEV_FLAGS_SYNC) ||
			(dtp->dev_flags & DEV_FLAGS_SYNC))
				i |= DDMA_CFG_SYNC;
		cp->ddma_cfg = i;
		wmb(); /* drain writebuffer */

		/*
		 * Return a non-zero value that can be used to find the channel
		 * information in subsequent operations.
		 */
		return (u32)(&chan_tab_ptr[chan]);
	}

	/* Release devices */
	stp->dev_flags &= ~DEV_FLAGS_INUSE;
	dtp->dev_flags &= ~DEV_FLAGS_INUSE;

	return 0;
}
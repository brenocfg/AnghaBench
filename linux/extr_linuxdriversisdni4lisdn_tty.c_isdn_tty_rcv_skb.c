#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
struct sk_buff {int* data; scalar_t__ len; } ;
struct TYPE_8__ {int* mdmreg; } ;
struct TYPE_10__ {int online; scalar_t__ rcvsched; int /*<<< orphan*/  readlock; TYPE_2__ emu; } ;
typedef  TYPE_4__ modem_info ;
struct TYPE_7__ {TYPE_4__* info; } ;
struct TYPE_11__ {int* m_idx; scalar_t__ modempoll; TYPE_3__** drv; TYPE_1__ mdm; } ;
struct TYPE_9__ {int /*<<< orphan*/ * rcvcount; int /*<<< orphan*/ * rpqueue; } ;

/* Variables and functions */
 int BIT_T70 ; 
 int BIT_T70_EXT ; 
 int /*<<< orphan*/  ISDN_TIMER_MODEMREAD ; 
 size_t REG_T70 ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 TYPE_6__* dev ; 
 int /*<<< orphan*/  isdn_timer_ctrl (int /*<<< orphan*/ ,int) ; 
 scalar_t__ isdn_tty_try_read (TYPE_4__*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
isdn_tty_rcv_skb(int i, int di, int channel, struct sk_buff *skb)
{
	ulong flags;
	int midx;
#ifdef CONFIG_ISDN_AUDIO
	int ifmt;
#endif
	modem_info *info;

	if ((midx = dev->m_idx[i]) < 0) {
		/* if midx is invalid, packet is not for tty */
		return 0;
	}
	info = &dev->mdm.info[midx];
#ifdef CONFIG_ISDN_AUDIO
	ifmt = 1;

	if ((info->vonline) && (!info->emu.vpar[4]))
		isdn_audio_calc_dtmf(info, skb->data, skb->len, ifmt);
	if ((info->vonline & 1) && (info->emu.vpar[1]))
		isdn_audio_calc_silence(info, skb->data, skb->len, ifmt);
#endif
	if ((info->online < 2)
#ifdef CONFIG_ISDN_AUDIO
	    && (!(info->vonline & 1))
#endif
		) {
		/* If Modem not listening, drop data */
		kfree_skb(skb);
		return 1;
	}
	if (info->emu.mdmreg[REG_T70] & BIT_T70) {
		if (info->emu.mdmreg[REG_T70] & BIT_T70_EXT) {
			/* T.70 decoding: throw away the T.70 header (2 or 4 bytes)   */
			if (skb->data[0] == 3) /* pure data packet -> 4 byte headers  */
				skb_pull(skb, 4);
			else
				if (skb->data[0] == 1) /* keepalive packet -> 2 byte hdr  */
					skb_pull(skb, 2);
		} else
			/* T.70 decoding: Simply throw away the T.70 header (4 bytes) */
			if ((skb->data[0] == 1) && ((skb->data[1] == 0) || (skb->data[1] == 1)))
				skb_pull(skb, 4);
	}
#ifdef CONFIG_ISDN_AUDIO
	ISDN_AUDIO_SKB_DLECOUNT(skb) = 0;
	ISDN_AUDIO_SKB_LOCK(skb) = 0;
	if (info->vonline & 1) {
		/* voice conversion/compression */
		switch (info->emu.vpar[3]) {
		case 2:
		case 3:
		case 4:
			/* adpcm
			 * Since compressed data takes less
			 * space, we can overwrite the buffer.
			 */
			skb_trim(skb, isdn_audio_xlaw2adpcm(info->adpcmr,
							    ifmt,
							    skb->data,
							    skb->data,
							    skb->len));
			break;
		case 5:
			/* a-law */
			if (!ifmt)
				isdn_audio_ulaw2alaw(skb->data, skb->len);
			break;
		case 6:
			/* u-law */
			if (ifmt)
				isdn_audio_alaw2ulaw(skb->data, skb->len);
			break;
		}
		ISDN_AUDIO_SKB_DLECOUNT(skb) =
			isdn_tty_countDLE(skb->data, skb->len);
	}
#ifdef CONFIG_ISDN_TTY_FAX
	else {
		if (info->faxonline & 2) {
			isdn_tty_fax_bitorder(info, skb);
			ISDN_AUDIO_SKB_DLECOUNT(skb) =
				isdn_tty_countDLE(skb->data, skb->len);
		}
	}
#endif
#endif
	/* Try to deliver directly via tty-buf if queue is empty */
	spin_lock_irqsave(&info->readlock, flags);
	if (skb_queue_empty(&dev->drv[di]->rpqueue[channel]))
		if (isdn_tty_try_read(info, skb)) {
			spin_unlock_irqrestore(&info->readlock, flags);
			return 1;
		}
	/* Direct deliver failed or queue wasn't empty.
	 * Queue up for later dequeueing via timer-irq.
	 */
	__skb_queue_tail(&dev->drv[di]->rpqueue[channel], skb);
	dev->drv[di]->rcvcount[channel] +=
		(skb->len
#ifdef CONFIG_ISDN_AUDIO
		 + ISDN_AUDIO_SKB_DLECOUNT(skb)
#endif
			);
	spin_unlock_irqrestore(&info->readlock, flags);
	/* Schedule dequeuing */
	if ((dev->modempoll) && (info->rcvsched))
		isdn_timer_ctrl(ISDN_TIMER_MODEMREAD, 1);
	return 1;
}
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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
typedef  int u_char ;
struct sk_buff {int len; } ;
struct TYPE_4__ {TYPE_1__** drv; } ;
struct TYPE_3__ {int* rcvcount; int /*<<< orphan*/ * rpqueue; } ;

/* Variables and functions */
 TYPE_2__* dev ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,int*,int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

int
isdn_readbchan(int di, int channel, u_char *buf, u_char *fp, int len, wait_queue_head_t *sleep)
{
	int count;
	int count_pull;
	int count_put;
	int dflag;
	struct sk_buff *skb;
	u_char *cp;

	if (!dev->drv[di])
		return 0;
	if (skb_queue_empty(&dev->drv[di]->rpqueue[channel])) {
		if (sleep)
			wait_event_interruptible(*sleep,
				!skb_queue_empty(&dev->drv[di]->rpqueue[channel]));
		else
			return 0;
	}
	if (len > dev->drv[di]->rcvcount[channel])
		len = dev->drv[di]->rcvcount[channel];
	cp = buf;
	count = 0;
	while (len) {
		if (!(skb = skb_peek(&dev->drv[di]->rpqueue[channel])))
			break;
#ifdef CONFIG_ISDN_AUDIO
		if (ISDN_AUDIO_SKB_LOCK(skb))
			break;
		ISDN_AUDIO_SKB_LOCK(skb) = 1;
		if ((ISDN_AUDIO_SKB_DLECOUNT(skb)) || (dev->drv[di]->DLEflag & (1 << channel))) {
			char *p = skb->data;
			unsigned long DLEmask = (1 << channel);

			dflag = 0;
			count_pull = count_put = 0;
			while ((count_pull < skb->len) && (len > 0)) {
				len--;
				if (dev->drv[di]->DLEflag & DLEmask) {
					*cp++ = DLE;
					dev->drv[di]->DLEflag &= ~DLEmask;
				} else {
					*cp++ = *p;
					if (*p == DLE) {
						dev->drv[di]->DLEflag |= DLEmask;
						(ISDN_AUDIO_SKB_DLECOUNT(skb))--;
					}
					p++;
					count_pull++;
				}
				count_put++;
			}
			if (count_pull >= skb->len)
				dflag = 1;
		} else {
#endif
			/* No DLE's in buff, so simply copy it */
			dflag = 1;
			if ((count_pull = skb->len) > len) {
				count_pull = len;
				dflag = 0;
			}
			count_put = count_pull;
			skb_copy_from_linear_data(skb, cp, count_put);
			cp += count_put;
			len -= count_put;
#ifdef CONFIG_ISDN_AUDIO
		}
#endif
		count += count_put;
		if (fp) {
			memset(fp, 0, count_put);
			fp += count_put;
		}
		if (dflag) {
			/* We got all the data in this buff.
			 * Now we can dequeue it.
			 */
			if (fp)
				*(fp - 1) = 0xff;
#ifdef CONFIG_ISDN_AUDIO
			ISDN_AUDIO_SKB_LOCK(skb) = 0;
#endif
			skb = skb_dequeue(&dev->drv[di]->rpqueue[channel]);
			dev_kfree_skb(skb);
		} else {
			/* Not yet emptied this buff, so it
			 * must stay in the queue, for further calls
			 * but we pull off the data we got until now.
			 */
			skb_pull(skb, count_pull);
#ifdef CONFIG_ISDN_AUDIO
			ISDN_AUDIO_SKB_LOCK(skb) = 0;
#endif
		}
		dev->drv[di]->rcvcount[channel] -= count_put;
	}
	return count;
}
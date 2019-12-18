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
typedef  scalar_t__ u8 ;
struct sk_buff {int dummy; } ;
struct nfcsim_link {scalar_t__ rf_tech; scalar_t__ mode; scalar_t__ cond; int /*<<< orphan*/  lock; scalar_t__ shutdown; struct sk_buff* skb; int /*<<< orphan*/  recv_wait; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 struct sk_buff* ERR_PTR (int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *nfcsim_link_recv_skb(struct nfcsim_link *link,
					    int timeout, u8 rf_tech, u8 mode)
{
	int rc;
	struct sk_buff *skb;

	rc = wait_event_interruptible_timeout(link->recv_wait,
					      link->cond,
					      msecs_to_jiffies(timeout));

	mutex_lock(&link->lock);

	skb = link->skb;
	link->skb = NULL;

	if (!rc) {
		rc = -ETIMEDOUT;
		goto done;
	}

	if (!skb || link->rf_tech != rf_tech || link->mode == mode) {
		rc = -EINVAL;
		goto done;
	}

	if (link->shutdown) {
		rc = -ENODEV;
		goto done;
	}

done:
	mutex_unlock(&link->lock);

	if (rc < 0) {
		dev_kfree_skb(skb);
		skb = ERR_PTR(rc);
	}

	link->cond = 0;

	return skb;
}
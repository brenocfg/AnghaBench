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
struct TYPE_2__ {int /*<<< orphan*/ * data; int /*<<< orphan*/ * notify_link_chg; } ;
struct lmac {int /*<<< orphan*/  event_cb_lock; TYPE_1__ event_cb; } ;
struct cgx {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 struct lmac* lmac_pdata (int,struct cgx*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int cgx_lmac_evh_unregister(void *cgxd, int lmac_id)
{
	struct lmac *lmac;
	unsigned long flags;
	struct cgx *cgx = cgxd;

	lmac = lmac_pdata(lmac_id, cgx);
	if (!lmac)
		return -ENODEV;

	spin_lock_irqsave(&lmac->event_cb_lock, flags);
	lmac->event_cb.notify_link_chg = NULL;
	lmac->event_cb.data = NULL;
	spin_unlock_irqrestore(&lmac->event_cb_lock, flags);

	return 0;
}
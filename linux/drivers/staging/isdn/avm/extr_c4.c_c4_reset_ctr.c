#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct capi_ctr {scalar_t__ driverdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  capi_ctrl; int /*<<< orphan*/  version; TYPE_2__* card; } ;
typedef  TYPE_1__ avmctrl_info ;
struct TYPE_5__ {size_t nr_controllers; scalar_t__ nlogcontr; TYPE_1__* ctrlinfo; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ avmcard ;

/* Variables and functions */
 int /*<<< orphan*/  c4_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  capi_ctr_down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void c4_reset_ctr(struct capi_ctr *ctrl)
{
	avmcard *card = ((avmctrl_info *)(ctrl->driverdata))->card;
	avmctrl_info *cinfo;
	u_int i;
	unsigned long flags;

	spin_lock_irqsave(&card->lock, flags);

	c4_reset(card);

	spin_unlock_irqrestore(&card->lock, flags);

	for (i = 0; i < card->nr_controllers; i++) {
		cinfo = &card->ctrlinfo[i];
		memset(cinfo->version, 0, sizeof(cinfo->version));
		capi_ctr_down(&cinfo->capi_ctrl);
	}
	card->nlogcontr = 0;
}
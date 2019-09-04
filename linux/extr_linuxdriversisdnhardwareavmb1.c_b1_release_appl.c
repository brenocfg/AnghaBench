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
typedef  int /*<<< orphan*/  u16 ;
struct capi_ctr {scalar_t__ driverdata; } ;
struct TYPE_3__ {int /*<<< orphan*/  ncci_head; TYPE_2__* card; } ;
typedef  TYPE_1__ avmctrl_info ;
struct TYPE_4__ {unsigned int port; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ avmcard ;

/* Variables and functions */
 int /*<<< orphan*/  SEND_RELEASE ; 
 int /*<<< orphan*/  b1_put_byte (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b1_put_word (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capilib_release_appl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void b1_release_appl(struct capi_ctr *ctrl, u16 appl)
{
	avmctrl_info *cinfo = (avmctrl_info *)(ctrl->driverdata);
	avmcard *card = cinfo->card;
	unsigned int port = card->port;
	unsigned long flags;

	spin_lock_irqsave(&card->lock, flags);
	capilib_release_appl(&cinfo->ncci_head, appl);
	b1_put_byte(port, SEND_RELEASE);
	b1_put_word(port, appl);
	spin_unlock_irqrestore(&card->lock, flags);
}
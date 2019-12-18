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
struct brcmf_fweh_info {int /*<<< orphan*/  event_q; int /*<<< orphan*/  evt_q_lock; int /*<<< orphan*/  event_work; } ;
struct brcmf_pub {struct brcmf_fweh_info fweh; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_fweh_event_worker ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void brcmf_fweh_attach(struct brcmf_pub *drvr)
{
	struct brcmf_fweh_info *fweh = &drvr->fweh;
	INIT_WORK(&fweh->event_work, brcmf_fweh_event_worker);
	spin_lock_init(&fweh->evt_q_lock);
	INIT_LIST_HEAD(&fweh->event_q);
}
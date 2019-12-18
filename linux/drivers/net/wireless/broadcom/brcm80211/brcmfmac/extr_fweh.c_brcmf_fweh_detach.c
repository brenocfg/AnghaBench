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
struct brcmf_fweh_info {int /*<<< orphan*/  evt_handler; int /*<<< orphan*/  event_q; int /*<<< orphan*/  event_work; } ;
struct brcmf_pub {struct brcmf_fweh_info fweh; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void brcmf_fweh_detach(struct brcmf_pub *drvr)
{
	struct brcmf_fweh_info *fweh = &drvr->fweh;

	/* cancel the worker */
	cancel_work_sync(&fweh->event_work);
	WARN_ON(!list_empty(&fweh->event_q));
	memset(fweh->evt_handler, 0, sizeof(fweh->evt_handler));
}
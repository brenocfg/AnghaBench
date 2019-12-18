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
typedef  scalar_t__ u_int ;
struct ahd_tmode_tstate {struct ahd_tmode_lstate** enabled_luns; } ;
struct ahd_tmode_lstate {int dummy; } ;
struct ahd_softc {struct ahd_tmode_tstate** enabled_targets; } ;
struct ahd_devinfo {size_t our_scsiid; int /*<<< orphan*/  target; int /*<<< orphan*/  channel; int /*<<< orphan*/  role; } ;
typedef  scalar_t__ cam_status ;

/* Variables and functions */
 int /*<<< orphan*/  AC_SENT_BDR ; 
 scalar_t__ AHD_NUM_LUNS ; 
 int /*<<< orphan*/  AHD_TRANS_CUR ; 
 scalar_t__ CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_SEL_TIMEOUT ; 
 int /*<<< orphan*/  MSG_BUS_DEV_RESET ; 
 int /*<<< orphan*/  MSG_EXT_WDTR_BUS_8_BIT ; 
 int /*<<< orphan*/  SCB_LIST_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 int ahd_abort_scbs (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ahd_name (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_queue_lstate_event (struct ahd_softc*,struct ahd_tmode_lstate*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_send_async (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_send_lstate_events (struct ahd_softc*,struct ahd_tmode_lstate*) ; 
 int /*<<< orphan*/  ahd_set_syncrate (struct ahd_softc*,struct ahd_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_set_width (struct ahd_softc*,struct ahd_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ahd_handle_devreset(struct ahd_softc *ahd, struct ahd_devinfo *devinfo,
		    u_int lun, cam_status status, char *message,
		    int verbose_level)
{
#ifdef AHD_TARGET_MODE
	struct ahd_tmode_tstate* tstate;
#endif
	int found;

	found = ahd_abort_scbs(ahd, devinfo->target, devinfo->channel,
			       lun, SCB_LIST_NULL, devinfo->role,
			       status);

#ifdef AHD_TARGET_MODE
	/*
	 * Send an immediate notify ccb to all target mord peripheral
	 * drivers affected by this action.
	 */
	tstate = ahd->enabled_targets[devinfo->our_scsiid];
	if (tstate != NULL) {
		u_int cur_lun;
		u_int max_lun;

		if (lun != CAM_LUN_WILDCARD) {
			cur_lun = 0;
			max_lun = AHD_NUM_LUNS - 1;
		} else {
			cur_lun = lun;
			max_lun = lun;
		}
		for (;cur_lun <= max_lun; cur_lun++) {
			struct ahd_tmode_lstate* lstate;

			lstate = tstate->enabled_luns[cur_lun];
			if (lstate == NULL)
				continue;

			ahd_queue_lstate_event(ahd, lstate, devinfo->our_scsiid,
					       MSG_BUS_DEV_RESET, /*arg*/0);
			ahd_send_lstate_events(ahd, lstate);
		}
	}
#endif

	/*
	 * Go back to async/narrow transfers and renegotiate.
	 */
	ahd_set_width(ahd, devinfo, MSG_EXT_WDTR_BUS_8_BIT,
		      AHD_TRANS_CUR, /*paused*/TRUE);
	ahd_set_syncrate(ahd, devinfo, /*period*/0, /*offset*/0,
			 /*ppr_options*/0, AHD_TRANS_CUR,
			 /*paused*/TRUE);
	
	if (status != CAM_SEL_TIMEOUT)
		ahd_send_async(ahd, devinfo->channel, devinfo->target,
			       CAM_LUN_WILDCARD, AC_SENT_BDR);

	if (message != NULL && bootverbose)
		printk("%s: %s on %c:%d. %d SCBs aborted\n", ahd_name(ahd),
		       message, devinfo->channel, devinfo->target, found);
}
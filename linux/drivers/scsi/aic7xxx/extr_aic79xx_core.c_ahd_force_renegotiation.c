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
struct ahd_tmode_tstate {int dummy; } ;
struct ahd_softc {int dummy; } ;
struct ahd_initiator_tinfo {int dummy; } ;
struct ahd_devinfo {int /*<<< orphan*/  target; int /*<<< orphan*/  our_scsiid; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_NEG_IF_NON_ASYNC ; 
 int AHD_SHOW_MESSAGES ; 
 int ahd_debug ; 
 struct ahd_initiator_tinfo* ahd_fetch_transinfo (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ahd_tmode_tstate**) ; 
 int /*<<< orphan*/  ahd_print_devinfo (struct ahd_softc*,struct ahd_devinfo*) ; 
 int /*<<< orphan*/  ahd_update_neg_request (struct ahd_softc*,struct ahd_devinfo*,struct ahd_tmode_tstate*,struct ahd_initiator_tinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void
ahd_force_renegotiation(struct ahd_softc *ahd, struct ahd_devinfo *devinfo)
{
	struct	ahd_initiator_tinfo *targ_info;
	struct	ahd_tmode_tstate *tstate;

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_MESSAGES) != 0) {
		ahd_print_devinfo(ahd, devinfo);
		printk("Forcing renegotiation\n");
	}
#endif
	targ_info = ahd_fetch_transinfo(ahd,
					devinfo->channel,
					devinfo->our_scsiid,
					devinfo->target,
					&tstate);
	ahd_update_neg_request(ahd, devinfo, tstate,
			       targ_info, AHD_NEG_IF_NON_ASYNC);
}
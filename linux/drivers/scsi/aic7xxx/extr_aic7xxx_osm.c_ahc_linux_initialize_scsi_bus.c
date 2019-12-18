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
typedef  int u_int ;
struct ahc_tmode_tstate {int dummy; } ;
struct ahc_softc {int flags; int features; int our_id; int our_id_b; } ;
struct ahc_initiator_tinfo {int dummy; } ;
struct ahc_devinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHC_NEG_ALWAYS ; 
 int AHC_RESET_BUS_A ; 
 int AHC_RESET_BUS_B ; 
 int AHC_TWIN ; 
 int AHC_WIDE ; 
 int /*<<< orphan*/  AIC7XXX_RESET_DELAY ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 int /*<<< orphan*/  ROLE_INITIATOR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ahc_compile_devinfo (struct ahc_devinfo*,int,int,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 struct ahc_initiator_tinfo* ahc_fetch_transinfo (struct ahc_softc*,char,int,int,struct ahc_tmode_tstate**) ; 
 int /*<<< orphan*/  ahc_linux_freeze_simq (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_linux_release_simq (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_lock (struct ahc_softc*,unsigned long*) ; 
 int /*<<< orphan*/  ahc_reset_channel (struct ahc_softc*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_unlock (struct ahc_softc*,unsigned long*) ; 
 int /*<<< orphan*/  ahc_update_neg_request (struct ahc_softc*,struct ahc_devinfo*,struct ahc_tmode_tstate*,struct ahc_initiator_tinfo*,int /*<<< orphan*/ ) ; 
 scalar_t__ aic7xxx_no_reset ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahc_linux_initialize_scsi_bus(struct ahc_softc *ahc)
{
	int i;
	int numtarg;
	unsigned long s;

	i = 0;
	numtarg = 0;

	ahc_lock(ahc, &s);

	if (aic7xxx_no_reset != 0)
		ahc->flags &= ~(AHC_RESET_BUS_A|AHC_RESET_BUS_B);

	if ((ahc->flags & AHC_RESET_BUS_A) != 0)
		ahc_reset_channel(ahc, 'A', /*initiate_reset*/TRUE);
	else
		numtarg = (ahc->features & AHC_WIDE) ? 16 : 8;

	if ((ahc->features & AHC_TWIN) != 0) {

		if ((ahc->flags & AHC_RESET_BUS_B) != 0) {
			ahc_reset_channel(ahc, 'B', /*initiate_reset*/TRUE);
		} else {
			if (numtarg == 0)
				i = 8;
			numtarg += 8;
		}
	}

	/*
	 * Force negotiation to async for all targets that
	 * will not see an initial bus reset.
	 */
	for (; i < numtarg; i++) {
		struct ahc_devinfo devinfo;
		struct ahc_initiator_tinfo *tinfo;
		struct ahc_tmode_tstate *tstate;
		u_int our_id;
		u_int target_id;
		char channel;

		channel = 'A';
		our_id = ahc->our_id;
		target_id = i;
		if (i > 7 && (ahc->features & AHC_TWIN) != 0) {
			channel = 'B';
			our_id = ahc->our_id_b;
			target_id = i % 8;
		}
		tinfo = ahc_fetch_transinfo(ahc, channel, our_id,
					    target_id, &tstate);
		ahc_compile_devinfo(&devinfo, our_id, target_id,
				    CAM_LUN_WILDCARD, channel, ROLE_INITIATOR);
		ahc_update_neg_request(ahc, &devinfo, tstate,
				       tinfo, AHC_NEG_ALWAYS);
	}
	ahc_unlock(ahc, &s);
	/* Give the bus some time to recover */
	if ((ahc->flags & (AHC_RESET_BUS_A|AHC_RESET_BUS_B)) != 0) {
		ahc_linux_freeze_simq(ahc);
		msleep(AIC7XXX_RESET_DELAY);
		ahc_linux_release_simq(ahc);
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct target_cmd {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  dmamap; } ;
struct ahd_softc {int qoutfifonext; scalar_t__ qoutfifonext_valid_tag; int flags; size_t tqinfifonext; TYPE_3__* targetcmds; int /*<<< orphan*/  tqinfifofnext; TYPE_2__ shared_data_map; int /*<<< orphan*/  shared_data_dmat; TYPE_1__* qoutfifo; } ;
struct TYPE_6__ {scalar_t__ cmd_valid; } ;
struct TYPE_4__ {scalar_t__ valid_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_RUN_QOUTFIFO ; 
 int /*<<< orphan*/  AHD_RUN_TQINFIFO ; 
 int AHD_TARGETROLE ; 
 int AHD_TQINFIFO_BLOCKED ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  ahd_dmamap_sync (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int ahd_targetcmd_offset (struct ahd_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
ahd_check_cmdcmpltqueues(struct ahd_softc *ahd)
{
	u_int retval;

	retval = 0;
	ahd_dmamap_sync(ahd, ahd->shared_data_dmat, ahd->shared_data_map.dmamap,
			/*offset*/ahd->qoutfifonext * sizeof(*ahd->qoutfifo),
			/*len*/sizeof(*ahd->qoutfifo), BUS_DMASYNC_POSTREAD);
	if (ahd->qoutfifo[ahd->qoutfifonext].valid_tag
	  == ahd->qoutfifonext_valid_tag)
		retval |= AHD_RUN_QOUTFIFO;
#ifdef AHD_TARGET_MODE
	if ((ahd->flags & AHD_TARGETROLE) != 0
	 && (ahd->flags & AHD_TQINFIFO_BLOCKED) == 0) {
		ahd_dmamap_sync(ahd, ahd->shared_data_dmat,
				ahd->shared_data_map.dmamap,
				ahd_targetcmd_offset(ahd, ahd->tqinfifofnext),
				/*len*/sizeof(struct target_cmd),
				BUS_DMASYNC_POSTREAD);
		if (ahd->targetcmds[ahd->tqinfifonext].cmd_valid != 0)
			retval |= AHD_RUN_TQINFIFO;
	}
#endif
	return (retval);
}
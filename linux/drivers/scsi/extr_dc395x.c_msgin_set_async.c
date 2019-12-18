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
struct ScsiReqBlk {int /*<<< orphan*/  state; struct DeviceCtlBlk* dcb; } ;
struct DeviceCtlBlk {int sync_mode; int min_nego_period; scalar_t__ sync_offset; int /*<<< orphan*/  target_lun; int /*<<< orphan*/  target_id; } ;
struct AdapterCtlBlk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_0 ; 
 int /*<<< orphan*/  DC395x_ENABLE_MSGOUT ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  SRB_DO_SYNC_NEGO ; 
 int SYNC_NEGO_DONE ; 
 int SYNC_NEGO_ENABLE ; 
 int WIDE_NEGO_DONE ; 
 int WIDE_NEGO_ENABLE ; 
 int /*<<< orphan*/  build_wdtr (struct AdapterCtlBlk*,struct DeviceCtlBlk*,struct ScsiReqBlk*) ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dprintkl (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reprogram_regs (struct AdapterCtlBlk*,struct DeviceCtlBlk*) ; 

__attribute__((used)) static void msgin_set_async(struct AdapterCtlBlk *acb, struct ScsiReqBlk *srb)
{
	struct DeviceCtlBlk *dcb = srb->dcb;
	dprintkl(KERN_DEBUG, "msgin_set_async: No sync transfers <%02i-%i>\n",
		dcb->target_id, dcb->target_lun);

	dcb->sync_mode &= ~(SYNC_NEGO_ENABLE);
	dcb->sync_mode |= SYNC_NEGO_DONE;
	/*dcb->sync_period &= 0; */
	dcb->sync_offset = 0;
	dcb->min_nego_period = 200 >> 2;	/* 200ns <=> 5 MHz */
	srb->state &= ~SRB_DO_SYNC_NEGO;
	reprogram_regs(acb, dcb);
	if ((dcb->sync_mode & WIDE_NEGO_ENABLE)
	    && !(dcb->sync_mode & WIDE_NEGO_DONE)) {
		build_wdtr(acb, dcb, srb);
		DC395x_ENABLE_MSGOUT;
		dprintkdbg(DBG_0, "msgin_set_async(rej): Try WDTR anyway\n");
	}
}
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
typedef  scalar_t__ u_int ;
struct scb {TYPE_3__* io_ctx; } ;
struct ahd_softc {int dummy; } ;
typedef  scalar_t__ role_t ;
struct TYPE_5__ {scalar_t__ tag_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  func_code; } ;
struct TYPE_6__ {TYPE_2__ csio; TYPE_1__ ccb_h; } ;

/* Variables and functions */
 char ALL_CHANNELS ; 
 int CAM_LUN_WILDCARD ; 
 int CAM_TARGET_WILDCARD ; 
 scalar_t__ ROLE_INITIATOR ; 
 scalar_t__ ROLE_TARGET ; 
 char SCB_GET_CHANNEL (struct ahd_softc*,struct scb*) ; 
 int SCB_GET_LUN (struct scb*) ; 
 scalar_t__ SCB_GET_TAG (struct scb*) ; 
 int SCB_GET_TARGET (struct ahd_softc*,struct scb*) ; 
 scalar_t__ SCB_LIST_NULL ; 
 int XPT_FC_GROUP (int /*<<< orphan*/ ) ; 
 int XPT_FC_GROUP_TMODE ; 

__attribute__((used)) static int
ahd_match_scb(struct ahd_softc *ahd, struct scb *scb, int target,
	      char channel, int lun, u_int tag, role_t role)
{
	int targ = SCB_GET_TARGET(ahd, scb);
	char chan = SCB_GET_CHANNEL(ahd, scb);
	int slun = SCB_GET_LUN(scb);
	int match;

	match = ((chan == channel) || (channel == ALL_CHANNELS));
	if (match != 0)
		match = ((targ == target) || (target == CAM_TARGET_WILDCARD));
	if (match != 0)
		match = ((lun == slun) || (lun == CAM_LUN_WILDCARD));
	if (match != 0) {
#ifdef AHD_TARGET_MODE
		int group;

		group = XPT_FC_GROUP(scb->io_ctx->ccb_h.func_code);
		if (role == ROLE_INITIATOR) {
			match = (group != XPT_FC_GROUP_TMODE)
			      && ((tag == SCB_GET_TAG(scb))
			       || (tag == SCB_LIST_NULL));
		} else if (role == ROLE_TARGET) {
			match = (group == XPT_FC_GROUP_TMODE)
			      && ((tag == scb->io_ctx->csio.tag_id)
			       || (tag == SCB_LIST_NULL));
		}
#else /* !AHD_TARGET_MODE */
		match = ((tag == SCB_GET_TAG(scb)) || (tag == SCB_LIST_NULL));
#endif /* AHD_TARGET_MODE */
	}

	return match;
}
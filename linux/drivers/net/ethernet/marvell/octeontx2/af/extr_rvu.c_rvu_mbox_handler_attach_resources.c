#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct rvu {int /*<<< orphan*/  rsrc_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcifunc; } ;
struct rsrc_attach {int sso; int ssow; int timlfs; int cptlfs; scalar_t__ modify; scalar_t__ nixlf; scalar_t__ npalf; TYPE_1__ hdr; } ;
struct msg_rsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKTYPE_CPT ; 
 int /*<<< orphan*/  BLKTYPE_NIX ; 
 int /*<<< orphan*/  BLKTYPE_NPA ; 
 int /*<<< orphan*/  BLKTYPE_SSO ; 
 int /*<<< orphan*/  BLKTYPE_SSOW ; 
 int /*<<< orphan*/  BLKTYPE_TIM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvu_attach_block (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rvu_check_rsrc_availability (struct rvu*,struct rsrc_attach*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_detach_block (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_detach_rsrcs (struct rvu*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rvu_mbox_handler_attach_resources(struct rvu *rvu,
					     struct rsrc_attach *attach,
					     struct msg_rsp *rsp)
{
	u16 pcifunc = attach->hdr.pcifunc;
	int err;

	/* If first request, detach all existing attached resources */
	if (!attach->modify)
		rvu_detach_rsrcs(rvu, NULL, pcifunc);

	mutex_lock(&rvu->rsrc_lock);

	/* Check if the request can be accommodated */
	err = rvu_check_rsrc_availability(rvu, attach, pcifunc);
	if (err)
		goto exit;

	/* Now attach the requested resources */
	if (attach->npalf)
		rvu_attach_block(rvu, pcifunc, BLKTYPE_NPA, 1);

	if (attach->nixlf)
		rvu_attach_block(rvu, pcifunc, BLKTYPE_NIX, 1);

	if (attach->sso) {
		/* RVU func doesn't know which exact LF or slot is attached
		 * to it, it always sees as slot 0,1,2. So for a 'modify'
		 * request, simply detach all existing attached LFs/slots
		 * and attach a fresh.
		 */
		if (attach->modify)
			rvu_detach_block(rvu, pcifunc, BLKTYPE_SSO);
		rvu_attach_block(rvu, pcifunc, BLKTYPE_SSO, attach->sso);
	}

	if (attach->ssow) {
		if (attach->modify)
			rvu_detach_block(rvu, pcifunc, BLKTYPE_SSOW);
		rvu_attach_block(rvu, pcifunc, BLKTYPE_SSOW, attach->ssow);
	}

	if (attach->timlfs) {
		if (attach->modify)
			rvu_detach_block(rvu, pcifunc, BLKTYPE_TIM);
		rvu_attach_block(rvu, pcifunc, BLKTYPE_TIM, attach->timlfs);
	}

	if (attach->cptlfs) {
		if (attach->modify)
			rvu_detach_block(rvu, pcifunc, BLKTYPE_CPT);
		rvu_attach_block(rvu, pcifunc, BLKTYPE_CPT, attach->cptlfs);
	}

exit:
	mutex_unlock(&rvu->rsrc_lock);
	return err;
}
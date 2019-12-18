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
struct TYPE_4__ {int /*<<< orphan*/  bmap; } ;
struct rvu_pfvf {int sso; int ssow; int timlfs; int cptlfs; TYPE_2__ msix; } ;
struct rvu_hwinfo {int /*<<< orphan*/ * block; } ;
struct rvu {struct rvu_hwinfo* hw; } ;
struct msix_offset_rsp {int sso; int ssow; int timlfs; int cptlfs; void** cptlf_msixoff; void** timlf_msixoff; void** ssow_msixoff; void** sso_msixoff; void* nix_msixoff; void* npa_msixoff; } ;
struct TYPE_3__ {int /*<<< orphan*/  pcifunc; } ;
struct msg_req {TYPE_1__ hdr; } ;

/* Variables and functions */
 size_t BLKADDR_CPT0 ; 
 size_t BLKADDR_NIX0 ; 
 size_t BLKADDR_NPA ; 
 size_t BLKADDR_SSO ; 
 size_t BLKADDR_SSOW ; 
 size_t BLKADDR_TIM ; 
 int rvu_get_lf (struct rvu*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* rvu_get_msix_offset (struct rvu*,struct rvu_pfvf*,size_t,int) ; 
 struct rvu_pfvf* rvu_get_pfvf (struct rvu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rvu_mbox_handler_msix_offset(struct rvu *rvu, struct msg_req *req,
					struct msix_offset_rsp *rsp)
{
	struct rvu_hwinfo *hw = rvu->hw;
	u16 pcifunc = req->hdr.pcifunc;
	struct rvu_pfvf *pfvf;
	int lf, slot;

	pfvf = rvu_get_pfvf(rvu, pcifunc);
	if (!pfvf->msix.bmap)
		return 0;

	/* Set MSIX offsets for each block's LFs attached to this PF/VF */
	lf = rvu_get_lf(rvu, &hw->block[BLKADDR_NPA], pcifunc, 0);
	rsp->npa_msixoff = rvu_get_msix_offset(rvu, pfvf, BLKADDR_NPA, lf);

	lf = rvu_get_lf(rvu, &hw->block[BLKADDR_NIX0], pcifunc, 0);
	rsp->nix_msixoff = rvu_get_msix_offset(rvu, pfvf, BLKADDR_NIX0, lf);

	rsp->sso = pfvf->sso;
	for (slot = 0; slot < rsp->sso; slot++) {
		lf = rvu_get_lf(rvu, &hw->block[BLKADDR_SSO], pcifunc, slot);
		rsp->sso_msixoff[slot] =
			rvu_get_msix_offset(rvu, pfvf, BLKADDR_SSO, lf);
	}

	rsp->ssow = pfvf->ssow;
	for (slot = 0; slot < rsp->ssow; slot++) {
		lf = rvu_get_lf(rvu, &hw->block[BLKADDR_SSOW], pcifunc, slot);
		rsp->ssow_msixoff[slot] =
			rvu_get_msix_offset(rvu, pfvf, BLKADDR_SSOW, lf);
	}

	rsp->timlfs = pfvf->timlfs;
	for (slot = 0; slot < rsp->timlfs; slot++) {
		lf = rvu_get_lf(rvu, &hw->block[BLKADDR_TIM], pcifunc, slot);
		rsp->timlf_msixoff[slot] =
			rvu_get_msix_offset(rvu, pfvf, BLKADDR_TIM, lf);
	}

	rsp->cptlfs = pfvf->cptlfs;
	for (slot = 0; slot < rsp->cptlfs; slot++) {
		lf = rvu_get_lf(rvu, &hw->block[BLKADDR_CPT0], pcifunc, slot);
		rsp->cptlf_msixoff[slot] =
			rvu_get_msix_offset(rvu, pfvf, BLKADDR_CPT0, lf);
	}
	return 0;
}
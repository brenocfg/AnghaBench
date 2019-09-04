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
typedef  size_t u8 ;
typedef  int u32 ;
struct amd64_pvt {int ecc_sym_sz; int fam; int model; int /*<<< orphan*/  dbam1; int /*<<< orphan*/  F3; TYPE_1__* umc; } ;
struct TYPE_2__ {int sdp_ctrl; int ecc_ctrl; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DBAM0 ; 
 int /*<<< orphan*/  EXT_NB_MCA_CFG ; 
 size_t NUM_UMCS ; 
 int UMC_SDP_INIT ; 
 int /*<<< orphan*/  amd64_read_dct_pci_cfg (struct amd64_pvt*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amd64_read_pci_cfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void determine_ecc_sym_sz(struct amd64_pvt *pvt)
{
	pvt->ecc_sym_sz = 4;

	if (pvt->umc) {
		u8 i;

		for (i = 0; i < NUM_UMCS; i++) {
			/* Check enabled channels only: */
			if ((pvt->umc[i].sdp_ctrl & UMC_SDP_INIT) &&
			    (pvt->umc[i].ecc_ctrl & BIT(7))) {
				pvt->ecc_sym_sz = 8;
				break;
			}
		}

		return;
	}

	if (pvt->fam >= 0x10) {
		u32 tmp;

		amd64_read_pci_cfg(pvt->F3, EXT_NB_MCA_CFG, &tmp);
		/* F16h has only DCT0, so no need to read dbam1. */
		if (pvt->fam != 0x16)
			amd64_read_dct_pci_cfg(pvt, 1, DBAM0, &pvt->dbam1);

		/* F10h, revD and later can do x8 ECC too. */
		if ((pvt->fam > 0x10 || pvt->model > 7) && tmp & BIT(25))
			pvt->ecc_sym_sz = 8;
	}
}
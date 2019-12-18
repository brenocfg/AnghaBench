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
struct TYPE_4__ {scalar_t__ e10g_unall; scalar_t__ e10g_lr; scalar_t__ e10g_lrm; scalar_t__ e10g_sr; } ;
union sfp_xcvr_e10g_code_u {int b; TYPE_2__ r; } ;
typedef  int u16 ;
struct TYPE_3__ {int* xcvr; } ;
struct sfp_mem_s {TYPE_1__ srlid_base; } ;
struct bfa_sfp_s {int* media; int state; scalar_t__ dbuf_kva; } ;
typedef  enum bfa_defs_sfp_media_e { ____Placeholder_bfa_defs_sfp_media_e } bfa_defs_sfp_media_e ;

/* Variables and functions */
 int BFA_SFP_MEDIA_CU ; 
 int BFA_SFP_MEDIA_EL ; 
 int BFA_SFP_MEDIA_LW ; 
 int BFA_SFP_MEDIA_SW ; 
 int BFA_SFP_MEDIA_UNKNOWN ; 
 int BFA_SFP_MEDIA_UNSUPPORT ; 
 int BFA_SFP_STATE_UNSUPPORT ; 
 int BFA_SFP_STATE_VALID ; 
 int SFP_XMTR_TECH_CA ; 
 int SFP_XMTR_TECH_CP ; 
 int SFP_XMTR_TECH_CU ; 
 int SFP_XMTR_TECH_EL_INTER ; 
 int SFP_XMTR_TECH_EL_INTRA ; 
 int SFP_XMTR_TECH_LC ; 
 int SFP_XMTR_TECH_LL ; 
 int SFP_XMTR_TECH_SA ; 
 int SFP_XMTR_TECH_SL ; 
 int SFP_XMTR_TECH_SN ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_sfp_s*,int) ; 

__attribute__((used)) static void
bfa_sfp_media_get(struct bfa_sfp_s *sfp)
{
	enum bfa_defs_sfp_media_e *media = sfp->media;

	*media = BFA_SFP_MEDIA_UNKNOWN;

	if (sfp->state == BFA_SFP_STATE_UNSUPPORT)
		*media = BFA_SFP_MEDIA_UNSUPPORT;
	else if (sfp->state == BFA_SFP_STATE_VALID) {
		union sfp_xcvr_e10g_code_u e10g;
		struct sfp_mem_s *sfpmem = (struct sfp_mem_s *)sfp->dbuf_kva;
		u16 xmtr_tech = (sfpmem->srlid_base.xcvr[4] & 0x3) << 7 |
				(sfpmem->srlid_base.xcvr[5] >> 1);

		e10g.b = sfpmem->srlid_base.xcvr[0];
		bfa_trc(sfp, e10g.b);
		bfa_trc(sfp, xmtr_tech);
		/* check fc transmitter tech */
		if ((xmtr_tech & SFP_XMTR_TECH_CU) ||
		    (xmtr_tech & SFP_XMTR_TECH_CP) ||
		    (xmtr_tech & SFP_XMTR_TECH_CA))
			*media = BFA_SFP_MEDIA_CU;
		else if ((xmtr_tech & SFP_XMTR_TECH_EL_INTRA) ||
			 (xmtr_tech & SFP_XMTR_TECH_EL_INTER))
			*media = BFA_SFP_MEDIA_EL;
		else if ((xmtr_tech & SFP_XMTR_TECH_LL) ||
			 (xmtr_tech & SFP_XMTR_TECH_LC))
			*media = BFA_SFP_MEDIA_LW;
		else if ((xmtr_tech & SFP_XMTR_TECH_SL) ||
			 (xmtr_tech & SFP_XMTR_TECH_SN) ||
			 (xmtr_tech & SFP_XMTR_TECH_SA))
			*media = BFA_SFP_MEDIA_SW;
		/* Check 10G Ethernet Compilance code */
		else if (e10g.r.e10g_sr)
			*media = BFA_SFP_MEDIA_SW;
		else if (e10g.r.e10g_lrm && e10g.r.e10g_lr)
			*media = BFA_SFP_MEDIA_LW;
		else if (e10g.r.e10g_unall)
			*media = BFA_SFP_MEDIA_UNKNOWN;
		else
			bfa_trc(sfp, 0);
	} else
		bfa_trc(sfp, sfp->state);
}
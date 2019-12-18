#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pkt_attrib {int vcs_mode; scalar_t__ ht_en; } ;
struct TYPE_5__ {scalar_t__ preamble_mode; } ;
struct TYPE_6__ {TYPE_1__ mlmext_info; } ;
struct adapter {TYPE_2__ mlmeextpriv; } ;
struct TYPE_7__ {int rtsen; int hw_rts_en; int cts2self; int rtsrate; int rts_ratefb_lmt; int rts_short; int /*<<< orphan*/  rts_sc; } ;
typedef  TYPE_3__* PTXDESC_8723B ;

/* Variables and functions */
#define  CTS_TO_SELF 130 
#define  NONE_VCS 129 
 scalar_t__ PREAMBLE_SHORT ; 
#define  RTS_CTS 128 
 int /*<<< orphan*/  SCMapping_8723B (struct adapter*,struct pkt_attrib*) ; 

__attribute__((used)) static void fill_txdesc_vcs_8723b(struct adapter *padapter, struct pkt_attrib *pattrib, PTXDESC_8723B ptxdesc)
{
	/* DBG_8192C("cvs_mode =%d\n", pattrib->vcs_mode); */

	if (pattrib->vcs_mode) {
		switch (pattrib->vcs_mode) {
		case RTS_CTS:
			ptxdesc->rtsen = 1;
			/*  ENABLE HW RTS */
			ptxdesc->hw_rts_en = 1;
			break;

		case CTS_TO_SELF:
			ptxdesc->cts2self = 1;
			break;

		case NONE_VCS:
		default:
			break;
		}

		ptxdesc->rtsrate = 8; /*  RTS Rate =24M */
		ptxdesc->rts_ratefb_lmt = 0xF;

		if (padapter->mlmeextpriv.mlmext_info.preamble_mode == PREAMBLE_SHORT)
			ptxdesc->rts_short = 1;

		/*  Set RTS BW */
		if (pattrib->ht_en)
			ptxdesc->rts_sc = SCMapping_8723B(padapter, pattrib);
	}
}
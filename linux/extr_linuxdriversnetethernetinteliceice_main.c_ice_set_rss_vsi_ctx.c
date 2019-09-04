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
typedef  int u8 ;
struct TYPE_6__ {int q_opt_rss; } ;
struct ice_vsi_ctx {TYPE_3__ info; } ;
struct ice_vsi {int type; TYPE_2__* back; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ICE_AQ_VSI_Q_OPT_RSS_HASH_M ; 
 int ICE_AQ_VSI_Q_OPT_RSS_HASH_S ; 
 int ICE_AQ_VSI_Q_OPT_RSS_LUT_M ; 
 int ICE_AQ_VSI_Q_OPT_RSS_LUT_PF ; 
 int ICE_AQ_VSI_Q_OPT_RSS_LUT_S ; 
 int ICE_AQ_VSI_Q_OPT_RSS_TPLZ ; 
#define  ICE_VSI_PF 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void ice_set_rss_vsi_ctx(struct ice_vsi_ctx *ctxt, struct ice_vsi *vsi)
{
	u8 lut_type, hash_type;

	switch (vsi->type) {
	case ICE_VSI_PF:
		/* PF VSI will inherit RSS instance of PF */
		lut_type = ICE_AQ_VSI_Q_OPT_RSS_LUT_PF;
		hash_type = ICE_AQ_VSI_Q_OPT_RSS_TPLZ;
		break;
	default:
		dev_warn(&vsi->back->pdev->dev, "Unknown VSI type %d\n",
			 vsi->type);
		return;
	}

	ctxt->info.q_opt_rss = ((lut_type << ICE_AQ_VSI_Q_OPT_RSS_LUT_S) &
				ICE_AQ_VSI_Q_OPT_RSS_LUT_M) |
				((hash_type << ICE_AQ_VSI_Q_OPT_RSS_HASH_S) &
				 ICE_AQ_VSI_Q_OPT_RSS_HASH_M);
}
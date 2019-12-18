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
struct vsp1_device {TYPE_1__* info; } ;
struct TYPE_2__ {unsigned int wpf_count; unsigned int rpf_count; unsigned int uds_count; unsigned int uif_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  VI6_CLK_DCSWT ; 
 int VI6_CLK_DCSWT_CSTPW_SHIFT ; 
 int VI6_CLK_DCSWT_CSTRW_SHIFT ; 
 int /*<<< orphan*/  VI6_DPR_BRU_ROUTE ; 
 int /*<<< orphan*/  VI6_DPR_CLU_ROUTE ; 
 int /*<<< orphan*/  VI6_DPR_HGO_SMPPT ; 
 int /*<<< orphan*/  VI6_DPR_HGT_SMPPT ; 
 int /*<<< orphan*/  VI6_DPR_HSI_ROUTE ; 
 int /*<<< orphan*/  VI6_DPR_HST_ROUTE ; 
 int /*<<< orphan*/  VI6_DPR_ILV_BRS_ROUTE ; 
 int /*<<< orphan*/  VI6_DPR_LUT_ROUTE ; 
 int VI6_DPR_NODE_UNUSED ; 
 int /*<<< orphan*/  VI6_DPR_RPF_ROUTE (unsigned int) ; 
 int VI6_DPR_SMPPT_PT_SHIFT ; 
 int VI6_DPR_SMPPT_TGW_SHIFT ; 
 int /*<<< orphan*/  VI6_DPR_SRU_ROUTE ; 
 int /*<<< orphan*/  VI6_DPR_UDS_ROUTE (unsigned int) ; 
 int /*<<< orphan*/  VI6_DPR_UIF_ROUTE (unsigned int) ; 
 int /*<<< orphan*/  VSP1_HAS_BRS ; 
 int /*<<< orphan*/  vsp1_dlm_setup (struct vsp1_device*) ; 
 scalar_t__ vsp1_feature (struct vsp1_device*,int /*<<< orphan*/ ) ; 
 int vsp1_reset_wpf (struct vsp1_device*,unsigned int) ; 
 int /*<<< orphan*/  vsp1_write (struct vsp1_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vsp1_device_init(struct vsp1_device *vsp1)
{
	unsigned int i;
	int ret;

	/* Reset any channel that might be running. */
	for (i = 0; i < vsp1->info->wpf_count; ++i) {
		ret = vsp1_reset_wpf(vsp1, i);
		if (ret < 0)
			return ret;
	}

	vsp1_write(vsp1, VI6_CLK_DCSWT, (8 << VI6_CLK_DCSWT_CSTPW_SHIFT) |
		   (8 << VI6_CLK_DCSWT_CSTRW_SHIFT));

	for (i = 0; i < vsp1->info->rpf_count; ++i)
		vsp1_write(vsp1, VI6_DPR_RPF_ROUTE(i), VI6_DPR_NODE_UNUSED);

	for (i = 0; i < vsp1->info->uds_count; ++i)
		vsp1_write(vsp1, VI6_DPR_UDS_ROUTE(i), VI6_DPR_NODE_UNUSED);

	for (i = 0; i < vsp1->info->uif_count; ++i)
		vsp1_write(vsp1, VI6_DPR_UIF_ROUTE(i), VI6_DPR_NODE_UNUSED);

	vsp1_write(vsp1, VI6_DPR_SRU_ROUTE, VI6_DPR_NODE_UNUSED);
	vsp1_write(vsp1, VI6_DPR_LUT_ROUTE, VI6_DPR_NODE_UNUSED);
	vsp1_write(vsp1, VI6_DPR_CLU_ROUTE, VI6_DPR_NODE_UNUSED);
	vsp1_write(vsp1, VI6_DPR_HST_ROUTE, VI6_DPR_NODE_UNUSED);
	vsp1_write(vsp1, VI6_DPR_HSI_ROUTE, VI6_DPR_NODE_UNUSED);
	vsp1_write(vsp1, VI6_DPR_BRU_ROUTE, VI6_DPR_NODE_UNUSED);

	if (vsp1_feature(vsp1, VSP1_HAS_BRS))
		vsp1_write(vsp1, VI6_DPR_ILV_BRS_ROUTE, VI6_DPR_NODE_UNUSED);

	vsp1_write(vsp1, VI6_DPR_HGO_SMPPT, (7 << VI6_DPR_SMPPT_TGW_SHIFT) |
		   (VI6_DPR_NODE_UNUSED << VI6_DPR_SMPPT_PT_SHIFT));
	vsp1_write(vsp1, VI6_DPR_HGT_SMPPT, (7 << VI6_DPR_SMPPT_TGW_SHIFT) |
		   (VI6_DPR_NODE_UNUSED << VI6_DPR_SMPPT_PT_SHIFT));

	vsp1_dlm_setup(vsp1);

	return 0;
}
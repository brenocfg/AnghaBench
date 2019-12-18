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
struct TYPE_2__ {int /*<<< orphan*/  enum_id; } ;
struct link_encoder {TYPE_1__ id; } ;
struct dcn10_link_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOG_DSC (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPHY_FEC_EN ; 
 int /*<<< orphan*/  DP_DPHY_CNTL ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn10_link_encoder* TO_DCN10_LINK_ENC (struct link_encoder*) ; 

void enc2_fec_set_enable(struct link_encoder *enc, bool enable)
{
	struct dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);
#ifdef CONFIG_DRM_AMD_DC_DSC_SUPPORT
	DC_LOG_DSC("%s FEC at link encoder inst %d",
			enable ? "Enabling" : "Disabling", enc->id.enum_id);
#endif
	REG_UPDATE(DP_DPHY_CNTL, DPHY_FEC_EN, enable);
}
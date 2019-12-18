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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct iavf_hw {int dummy; } ;
struct iavf_aqc_get_set_rss_lut {int /*<<< orphan*/  flags; int /*<<< orphan*/  vsi_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct iavf_aq_desc {int /*<<< orphan*/  flags; TYPE_1__ params; } ;
typedef  enum iavf_status { ____Placeholder_iavf_status } iavf_status ;

/* Variables and functions */
 int IAVF_AQC_SET_RSS_LUT_TABLE_TYPE_MASK ; 
 int IAVF_AQC_SET_RSS_LUT_TABLE_TYPE_PF ; 
 int IAVF_AQC_SET_RSS_LUT_TABLE_TYPE_SHIFT ; 
 int IAVF_AQC_SET_RSS_LUT_TABLE_TYPE_VSI ; 
 int IAVF_AQC_SET_RSS_LUT_VSI_ID_MASK ; 
 int IAVF_AQC_SET_RSS_LUT_VSI_ID_SHIFT ; 
 scalar_t__ IAVF_AQC_SET_RSS_LUT_VSI_VALID ; 
 scalar_t__ IAVF_AQ_FLAG_BUF ; 
 scalar_t__ IAVF_AQ_FLAG_RD ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  iavf_aqc_opc_get_rss_lut ; 
 int /*<<< orphan*/  iavf_aqc_opc_set_rss_lut ; 
 int iavf_asq_send_command (struct iavf_hw*,struct iavf_aq_desc*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iavf_fill_default_direct_cmd_desc (struct iavf_aq_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum iavf_status iavf_aq_get_set_rss_lut(struct iavf_hw *hw,
						u16 vsi_id, bool pf_lut,
						u8 *lut, u16 lut_size,
						bool set)
{
	enum iavf_status status;
	struct iavf_aq_desc desc;
	struct iavf_aqc_get_set_rss_lut *cmd_resp =
		   (struct iavf_aqc_get_set_rss_lut *)&desc.params.raw;

	if (set)
		iavf_fill_default_direct_cmd_desc(&desc,
						  iavf_aqc_opc_set_rss_lut);
	else
		iavf_fill_default_direct_cmd_desc(&desc,
						  iavf_aqc_opc_get_rss_lut);

	/* Indirect command */
	desc.flags |= cpu_to_le16((u16)IAVF_AQ_FLAG_BUF);
	desc.flags |= cpu_to_le16((u16)IAVF_AQ_FLAG_RD);

	cmd_resp->vsi_id =
			cpu_to_le16((u16)((vsi_id <<
					  IAVF_AQC_SET_RSS_LUT_VSI_ID_SHIFT) &
					  IAVF_AQC_SET_RSS_LUT_VSI_ID_MASK));
	cmd_resp->vsi_id |= cpu_to_le16((u16)IAVF_AQC_SET_RSS_LUT_VSI_VALID);

	if (pf_lut)
		cmd_resp->flags |= cpu_to_le16((u16)
					((IAVF_AQC_SET_RSS_LUT_TABLE_TYPE_PF <<
					IAVF_AQC_SET_RSS_LUT_TABLE_TYPE_SHIFT) &
					IAVF_AQC_SET_RSS_LUT_TABLE_TYPE_MASK));
	else
		cmd_resp->flags |= cpu_to_le16((u16)
					((IAVF_AQC_SET_RSS_LUT_TABLE_TYPE_VSI <<
					IAVF_AQC_SET_RSS_LUT_TABLE_TYPE_SHIFT) &
					IAVF_AQC_SET_RSS_LUT_TABLE_TYPE_MASK));

	status = iavf_asq_send_command(hw, &desc, lut, lut_size, NULL);

	return status;
}
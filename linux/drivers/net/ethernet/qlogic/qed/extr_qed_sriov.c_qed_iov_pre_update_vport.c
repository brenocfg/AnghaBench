#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct qed_filter_accept_flags {int rx_accept_filter; int tx_accept_filter; scalar_t__ update_tx_mode_config; scalar_t__ update_rx_mode_config; } ;
struct qed_sp_vport_update_params {struct qed_filter_accept_flags accept_flags; } ;
struct qed_public_vf_info {int rx_accept_mode; int tx_accept_mode; int /*<<< orphan*/  is_trusted_configured; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int QED_ACCEPT_MCAST_UNMATCHED ; 
 int QED_ACCEPT_UCAST_UNMATCHED ; 
 int /*<<< orphan*/  QED_IOV_VP_UPDATE_ACCEPT_PARAM ; 
 struct qed_public_vf_info* qed_iov_get_public_vf_info (struct qed_hwfn*,int,int) ; 

__attribute__((used)) static int qed_iov_pre_update_vport(struct qed_hwfn *hwfn,
				    u8 vfid,
				    struct qed_sp_vport_update_params *params,
				    u16 *tlvs)
{
	u8 mask = QED_ACCEPT_UCAST_UNMATCHED | QED_ACCEPT_MCAST_UNMATCHED;
	struct qed_filter_accept_flags *flags = &params->accept_flags;
	struct qed_public_vf_info *vf_info;

	/* Untrusted VFs can't even be trusted to know that fact.
	 * Simply indicate everything is configured fine, and trace
	 * configuration 'behind their back'.
	 */
	if (!(*tlvs & BIT(QED_IOV_VP_UPDATE_ACCEPT_PARAM)))
		return 0;

	vf_info = qed_iov_get_public_vf_info(hwfn, vfid, true);

	if (flags->update_rx_mode_config) {
		vf_info->rx_accept_mode = flags->rx_accept_filter;
		if (!vf_info->is_trusted_configured)
			flags->rx_accept_filter &= ~mask;
	}

	if (flags->update_tx_mode_config) {
		vf_info->tx_accept_mode = flags->tx_accept_filter;
		if (!vf_info->is_trusted_configured)
			flags->tx_accept_filter &= ~mask;
	}

	return 0;
}
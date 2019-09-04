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
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
typedef  enum qed_mib_read_type { ____Placeholder_qed_mib_read_type } qed_mib_read_type ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*,int) ; 
 int EINVAL ; 
#define  QED_DCBX_LOCAL_LLDP_MIB 132 
#define  QED_DCBX_LOCAL_MIB 131 
#define  QED_DCBX_OPERATIONAL_MIB 130 
#define  QED_DCBX_REMOTE_LLDP_MIB 129 
#define  QED_DCBX_REMOTE_MIB 128 
 int qed_dcbx_read_local_lldp_mib (struct qed_hwfn*,struct qed_ptt*) ; 
 int qed_dcbx_read_local_mib (struct qed_hwfn*,struct qed_ptt*) ; 
 int qed_dcbx_read_operational_mib (struct qed_hwfn*,struct qed_ptt*,int) ; 
 int qed_dcbx_read_remote_lldp_mib (struct qed_hwfn*,struct qed_ptt*,int) ; 
 int qed_dcbx_read_remote_mib (struct qed_hwfn*,struct qed_ptt*,int) ; 

__attribute__((used)) static int qed_dcbx_read_mib(struct qed_hwfn *p_hwfn,
			     struct qed_ptt *p_ptt, enum qed_mib_read_type type)
{
	int rc = -EINVAL;

	switch (type) {
	case QED_DCBX_OPERATIONAL_MIB:
		rc = qed_dcbx_read_operational_mib(p_hwfn, p_ptt, type);
		break;
	case QED_DCBX_REMOTE_MIB:
		rc = qed_dcbx_read_remote_mib(p_hwfn, p_ptt, type);
		break;
	case QED_DCBX_LOCAL_MIB:
		rc = qed_dcbx_read_local_mib(p_hwfn, p_ptt);
		break;
	case QED_DCBX_REMOTE_LLDP_MIB:
		rc = qed_dcbx_read_remote_lldp_mib(p_hwfn, p_ptt, type);
		break;
	case QED_DCBX_LOCAL_LLDP_MIB:
		rc = qed_dcbx_read_local_lldp_mib(p_hwfn, p_ptt);
		break;
	default:
		DP_ERR(p_hwfn, "MIB read err, unknown mib type %d\n", type);
	}

	return rc;
}
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
struct qed_hwfn {int dummy; } ;
struct qed_dcbx_get {int dummy; } ;
typedef  enum qed_mib_read_type { ____Placeholder_qed_mib_read_type } qed_mib_read_type ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*,int) ; 
 int EINVAL ; 
#define  QED_DCBX_LOCAL_LLDP_MIB 132 
#define  QED_DCBX_LOCAL_MIB 131 
#define  QED_DCBX_OPERATIONAL_MIB 130 
#define  QED_DCBX_REMOTE_LLDP_MIB 129 
#define  QED_DCBX_REMOTE_MIB 128 
 int /*<<< orphan*/  qed_dcbx_get_local_lldp_params (struct qed_hwfn*,struct qed_dcbx_get*) ; 
 int /*<<< orphan*/  qed_dcbx_get_local_params (struct qed_hwfn*,struct qed_dcbx_get*) ; 
 int /*<<< orphan*/  qed_dcbx_get_operational_params (struct qed_hwfn*,struct qed_dcbx_get*) ; 
 int /*<<< orphan*/  qed_dcbx_get_remote_lldp_params (struct qed_hwfn*,struct qed_dcbx_get*) ; 
 int /*<<< orphan*/  qed_dcbx_get_remote_params (struct qed_hwfn*,struct qed_dcbx_get*) ; 

__attribute__((used)) static int
qed_dcbx_get_params(struct qed_hwfn *p_hwfn, struct qed_dcbx_get *p_params,
		    enum qed_mib_read_type type)
{
	switch (type) {
	case QED_DCBX_REMOTE_MIB:
		qed_dcbx_get_remote_params(p_hwfn, p_params);
		break;
	case QED_DCBX_LOCAL_MIB:
		qed_dcbx_get_local_params(p_hwfn, p_params);
		break;
	case QED_DCBX_OPERATIONAL_MIB:
		qed_dcbx_get_operational_params(p_hwfn, p_params);
		break;
	case QED_DCBX_REMOTE_LLDP_MIB:
		qed_dcbx_get_remote_lldp_params(p_hwfn, p_params);
		break;
	case QED_DCBX_LOCAL_LLDP_MIB:
		qed_dcbx_get_local_lldp_params(p_hwfn, p_params);
		break;
	default:
		DP_ERR(p_hwfn, "MIB read err, unknown mib type %d\n", type);
		return -EINVAL;
	}

	return 0;
}
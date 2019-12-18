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
typedef  scalar_t__ u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct qed_dcbx_mib_meta_data {TYPE_1__* mib; int /*<<< orphan*/  size; int /*<<< orphan*/  addr; TYPE_1__* lldp_remote; } ;
typedef  enum qed_mib_read_type { ____Placeholder_qed_mib_read_type } qed_mib_read_type ;
struct TYPE_2__ {scalar_t__ prefix_seq_num; scalar_t__ suffix_seq_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*,int,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int,int,scalar_t__,scalar_t__) ; 
 int EIO ; 
 int QED_DCBX_MAX_MIB_READ_TRY ; 
 int QED_DCBX_REMOTE_LLDP_MIB ; 
 int /*<<< orphan*/  QED_MSG_DCB ; 
 int /*<<< orphan*/  qed_memcpy_from (struct qed_hwfn*,struct qed_ptt*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qed_dcbx_copy_mib(struct qed_hwfn *p_hwfn,
		  struct qed_ptt *p_ptt,
		  struct qed_dcbx_mib_meta_data *p_data,
		  enum qed_mib_read_type type)
{
	u32 prefix_seq_num, suffix_seq_num;
	int read_count = 0;
	int rc = 0;

	/* The data is considered to be valid only if both sequence numbers are
	 * the same.
	 */
	do {
		if (type == QED_DCBX_REMOTE_LLDP_MIB) {
			qed_memcpy_from(p_hwfn, p_ptt, p_data->lldp_remote,
					p_data->addr, p_data->size);
			prefix_seq_num = p_data->lldp_remote->prefix_seq_num;
			suffix_seq_num = p_data->lldp_remote->suffix_seq_num;
		} else {
			qed_memcpy_from(p_hwfn, p_ptt, p_data->mib,
					p_data->addr, p_data->size);
			prefix_seq_num = p_data->mib->prefix_seq_num;
			suffix_seq_num = p_data->mib->suffix_seq_num;
		}
		read_count++;

		DP_VERBOSE(p_hwfn,
			   QED_MSG_DCB,
			   "mib type = %d, try count = %d prefix seq num  = %d suffix seq num = %d\n",
			   type, read_count, prefix_seq_num, suffix_seq_num);
	} while ((prefix_seq_num != suffix_seq_num) &&
		 (read_count < QED_DCBX_MAX_MIB_READ_TRY));

	if (read_count >= QED_DCBX_MAX_MIB_READ_TRY) {
		DP_ERR(p_hwfn,
		       "MIB read err, mib type = %d, try count = %d prefix seq num = %d suffix seq num = %d\n",
		       type, read_count, prefix_seq_num, suffix_seq_num);
		rc = -EIO;
	}

	return rc;
}
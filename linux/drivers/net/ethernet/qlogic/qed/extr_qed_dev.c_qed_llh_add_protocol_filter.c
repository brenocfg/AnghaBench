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
struct TYPE_2__ {int type; void* dest_port; void* source_port_or_eth_type; } ;
union qed_llh_filter {TYPE_1__ protocol; } ;
typedef  int u8 ;
typedef  int u32 ;
typedef  void* u16 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct qed_dev {int /*<<< orphan*/  mf_bits; } ;
typedef  int /*<<< orphan*/  str ;
typedef  enum qed_llh_prot_filter_type_t { ____Placeholder_qed_llh_prot_filter_type_t } qed_llh_prot_filter_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int*,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_dev*,int /*<<< orphan*/ ,char*,int*,int,int,int,int) ; 
 int EAGAIN ; 
 struct qed_hwfn* QED_LEADING_HWFN (struct qed_dev*) ; 
 int /*<<< orphan*/  QED_LLH_FILTER_TYPE_PROTOCOL ; 
 int /*<<< orphan*/  QED_MF_LLH_PROTO_CLSS ; 
 int /*<<< orphan*/  QED_MSG_SP ; 
 int qed_llh_abs_ppfid (struct qed_dev*,int,int*) ; 
 int qed_llh_add_filter (struct qed_hwfn*,struct qed_ptt*,int,int,int,int,int) ; 
 int qed_llh_protocol_filter_stringify (struct qed_dev*,int,void*,void*,int*,int) ; 
 int qed_llh_protocol_filter_to_hilo (struct qed_dev*,int,void*,void*,int*,int*) ; 
 int qed_llh_shadow_add_filter (struct qed_dev*,int,int /*<<< orphan*/ ,union qed_llh_filter*,int*,int*) ; 
 struct qed_ptt* qed_ptt_acquire (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_ptt_release (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
qed_llh_add_protocol_filter(struct qed_dev *cdev,
			    u8 ppfid,
			    enum qed_llh_prot_filter_type_t type,
			    u16 source_port_or_eth_type, u16 dest_port)
{
	struct qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	struct qed_ptt *p_ptt = qed_ptt_acquire(p_hwfn);
	u8 filter_idx, abs_ppfid, str[32], type_bitmap;
	union qed_llh_filter filter = {};
	u32 high, low, ref_cnt;
	int rc = 0;

	if (!p_ptt)
		return -EAGAIN;

	if (!test_bit(QED_MF_LLH_PROTO_CLSS, &cdev->mf_bits))
		goto out;

	rc = qed_llh_protocol_filter_stringify(cdev, type,
					       source_port_or_eth_type,
					       dest_port, str, sizeof(str));
	if (rc)
		goto err;

	filter.protocol.type = type;
	filter.protocol.source_port_or_eth_type = source_port_or_eth_type;
	filter.protocol.dest_port = dest_port;
	rc = qed_llh_shadow_add_filter(cdev,
				       ppfid,
				       QED_LLH_FILTER_TYPE_PROTOCOL,
				       &filter, &filter_idx, &ref_cnt);
	if (rc)
		goto err;

	rc = qed_llh_abs_ppfid(cdev, ppfid, &abs_ppfid);
	if (rc)
		goto err;

	/* Configure the LLH only in case of a new the filter */
	if (ref_cnt == 1) {
		rc = qed_llh_protocol_filter_to_hilo(cdev, type,
						     source_port_or_eth_type,
						     dest_port, &high, &low);
		if (rc)
			goto err;

		type_bitmap = 0x1 << type;
		rc = qed_llh_add_filter(p_hwfn, p_ptt, abs_ppfid,
					filter_idx, type_bitmap, high, low);
		if (rc)
			goto err;
	}

	DP_VERBOSE(cdev,
		   QED_MSG_SP,
		   "LLH: Added protocol filter [%s] to ppfid %hhd [abs %hhd] at idx %hhd [ref_cnt %d]\n",
		   str, ppfid, abs_ppfid, filter_idx, ref_cnt);

	goto out;

err:	DP_NOTICE(p_hwfn,
		  "LLH: Failed to add protocol filter [%s] to ppfid %hhd\n",
		  str, ppfid);
out:
	qed_ptt_release(p_hwfn, p_ptt);

	return rc;
}
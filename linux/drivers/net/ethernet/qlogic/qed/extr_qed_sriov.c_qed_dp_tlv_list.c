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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct tlv_buffer_size {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct channel_tlv {scalar_t__ type; scalar_t__ length; } ;

/* Variables and functions */
 scalar_t__ CHANNEL_TLV_LIST_END ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 

void qed_dp_tlv_list(struct qed_hwfn *p_hwfn, void *tlvs_list)
{
	u16 i = 1, total_length = 0;
	struct channel_tlv *tlv;

	do {
		tlv = (struct channel_tlv *)((u8 *)tlvs_list + total_length);

		/* output tlv */
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "TLV number %d: type %d, length %d\n",
			   i, tlv->type, tlv->length);

		if (tlv->type == CHANNEL_TLV_LIST_END)
			return;

		/* Validate entry - protect against malicious VFs */
		if (!tlv->length) {
			DP_NOTICE(p_hwfn, "TLV of length 0 found\n");
			return;
		}

		total_length += tlv->length;

		if (total_length >= sizeof(struct tlv_buffer_size)) {
			DP_NOTICE(p_hwfn, "TLV ==> Buffer overflow\n");
			return;
		}

		i++;
	} while (1);
}
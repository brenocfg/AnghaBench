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
struct qtnf_mac_info {int /*<<< orphan*/  coverage_class; int /*<<< orphan*/  lretry_limit; int /*<<< orphan*/  sretry_limit; void* rts_thr; void* frag_thr; } ;
struct qtnf_wmac {int /*<<< orphan*/  macid; struct qtnf_mac_info macinfo; } ;
struct qlink_tlv_rlimit {int /*<<< orphan*/  rlimit; } ;
struct qlink_tlv_hdr {scalar_t__ val; int /*<<< orphan*/  type; int /*<<< orphan*/  len; } ;
struct qlink_tlv_frag_rts_thr {int /*<<< orphan*/  thr; } ;
struct qlink_tlv_cclass {int /*<<< orphan*/  cclass; } ;

/* Variables and functions */
 int EINVAL ; 
#define  QTN_TLV_ID_COVERAGE_CLASS 132 
#define  QTN_TLV_ID_FRAG_THRESH 131 
#define  QTN_TLV_ID_LRETRY_LIMIT 130 
#define  QTN_TLV_ID_RTS_THRESH 129 
#define  QTN_TLV_ID_SRETRY_LIMIT 128 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,size_t,...) ; 

__attribute__((used)) static int qtnf_cmd_resp_proc_phy_params(struct qtnf_wmac *mac,
					 const u8 *payload, size_t payload_len)
{
	struct qtnf_mac_info *mac_info;
	struct qlink_tlv_frag_rts_thr *phy_thr;
	struct qlink_tlv_rlimit *limit;
	struct qlink_tlv_cclass *class;
	u16 tlv_type;
	u16 tlv_value_len;
	size_t tlv_full_len;
	const struct qlink_tlv_hdr *tlv;

	mac_info = &mac->macinfo;

	tlv = (struct qlink_tlv_hdr *)payload;
	while (payload_len >= sizeof(struct qlink_tlv_hdr)) {
		tlv_type = le16_to_cpu(tlv->type);
		tlv_value_len = le16_to_cpu(tlv->len);
		tlv_full_len = tlv_value_len + sizeof(struct qlink_tlv_hdr);

		if (tlv_full_len > payload_len) {
			pr_warn("MAC%u: malformed TLV 0x%.2X; LEN: %u\n",
				mac->macid, tlv_type, tlv_value_len);
			return -EINVAL;
		}

		switch (tlv_type) {
		case QTN_TLV_ID_FRAG_THRESH:
			phy_thr = (void *)tlv;
			mac_info->frag_thr = le32_to_cpu(phy_thr->thr);
			break;
		case QTN_TLV_ID_RTS_THRESH:
			phy_thr = (void *)tlv;
			mac_info->rts_thr = le32_to_cpu(phy_thr->thr);
			break;
		case QTN_TLV_ID_SRETRY_LIMIT:
			limit = (void *)tlv;
			mac_info->sretry_limit = limit->rlimit;
			break;
		case QTN_TLV_ID_LRETRY_LIMIT:
			limit = (void *)tlv;
			mac_info->lretry_limit = limit->rlimit;
			break;
		case QTN_TLV_ID_COVERAGE_CLASS:
			class = (void *)tlv;
			mac_info->coverage_class = class->cclass;
			break;
		default:
			pr_err("MAC%u: Unknown TLV type: %#x\n", mac->macid,
			       le16_to_cpu(tlv->type));
			break;
		}

		payload_len -= tlv_full_len;
		tlv = (struct qlink_tlv_hdr *)(tlv->val + tlv_value_len);
	}

	if (payload_len) {
		pr_warn("MAC%u: malformed TLV buf; bytes left: %zu\n",
			mac->macid, payload_len);
		return -EINVAL;
	}

	return 0;
}
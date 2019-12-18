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
struct qtnf_chan_stats {int /*<<< orphan*/  chan_noise; void* cca_busy; void* cca_try; void* chan_num; void* cca_rx; void* cca_tx; } ;
struct qlink_tlv_hdr {scalar_t__ val; int /*<<< orphan*/  type; int /*<<< orphan*/  len; } ;
struct qlink_chan_stats {int /*<<< orphan*/  chan_noise; int /*<<< orphan*/  cca_try; int /*<<< orphan*/  cca_busy; int /*<<< orphan*/  cca_rx; int /*<<< orphan*/  cca_tx; int /*<<< orphan*/  chan_num; } ;

/* Variables and functions */
 int EINVAL ; 
#define  QTN_TLV_ID_CHANNEL_STATS 128 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,void*,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,size_t,...) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static int
qtnf_cmd_resp_proc_chan_stat_info(struct qtnf_chan_stats *stats,
				  const u8 *payload, size_t payload_len)
{
	struct qlink_chan_stats *qlink_stats;
	const struct qlink_tlv_hdr *tlv;
	size_t tlv_full_len;
	u16 tlv_value_len;
	u16 tlv_type;

	tlv = (struct qlink_tlv_hdr *)payload;
	while (payload_len >= sizeof(struct qlink_tlv_hdr)) {
		tlv_type = le16_to_cpu(tlv->type);
		tlv_value_len = le16_to_cpu(tlv->len);
		tlv_full_len = tlv_value_len + sizeof(struct qlink_tlv_hdr);
		if (tlv_full_len > payload_len) {
			pr_warn("malformed TLV 0x%.2X; LEN: %u\n",
				tlv_type, tlv_value_len);
			return -EINVAL;
		}
		switch (tlv_type) {
		case QTN_TLV_ID_CHANNEL_STATS:
			if (unlikely(tlv_value_len != sizeof(*qlink_stats))) {
				pr_err("invalid CHANNEL_STATS entry size\n");
				return -EINVAL;
			}

			qlink_stats = (void *)tlv->val;

			stats->chan_num = le32_to_cpu(qlink_stats->chan_num);
			stats->cca_tx = le32_to_cpu(qlink_stats->cca_tx);
			stats->cca_rx = le32_to_cpu(qlink_stats->cca_rx);
			stats->cca_busy = le32_to_cpu(qlink_stats->cca_busy);
			stats->cca_try = le32_to_cpu(qlink_stats->cca_try);
			stats->chan_noise = qlink_stats->chan_noise;

			pr_debug("chan(%u) try(%u) busy(%u) noise(%d)\n",
				 stats->chan_num, stats->cca_try,
				 stats->cca_busy, stats->chan_noise);
			break;
		default:
			pr_warn("Unknown TLV type: %#x\n",
				le16_to_cpu(tlv->type));
		}
		payload_len -= tlv_full_len;
		tlv = (struct qlink_tlv_hdr *)(tlv->val + tlv_value_len);
	}

	if (payload_len) {
		pr_warn("malformed TLV buf; bytes left: %zu\n", payload_len);
		return -EINVAL;
	}

	return 0;
}
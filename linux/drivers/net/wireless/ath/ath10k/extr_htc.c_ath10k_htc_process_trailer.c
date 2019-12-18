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
struct TYPE_2__ {int len; int id; } ;
struct ath10k_htc_record {TYPE_1__ hdr; struct ath10k_htc_lookahead_bundle* lookahead_bundle; int /*<<< orphan*/  lookahead_report; int /*<<< orphan*/  credit_report; } ;
struct ath10k_htc_lookahead_report {int dummy; } ;
struct ath10k_htc_lookahead_bundle {int dummy; } ;
struct ath10k_htc_credit_report {int dummy; } ;
struct ath10k_htc {struct ath10k* ar; } ;
struct ath10k {int dummy; } ;
typedef  enum ath10k_htc_ep_id { ____Placeholder_ath10k_htc_ep_id } ath10k_htc_ep_id ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_HTC ; 
#define  ATH10K_HTC_RECORD_CREDITS 130 
#define  ATH10K_HTC_RECORD_LOOKAHEAD 129 
#define  ATH10K_HTC_RECORD_LOOKAHEAD_BUNDLE 128 
 int EINVAL ; 
 int /*<<< orphan*/  ath10k_dbg_dump (struct ath10k*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ath10k_htc_process_credit_report (struct ath10k_htc*,int /*<<< orphan*/ ,size_t,int) ; 
 int ath10k_htc_process_lookahead (struct ath10k_htc*,int /*<<< orphan*/ ,size_t,int,void*,int*) ; 
 int ath10k_htc_process_lookahead_bundle (struct ath10k_htc*,struct ath10k_htc_lookahead_bundle*,size_t,int,void*,int*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,...) ; 

int ath10k_htc_process_trailer(struct ath10k_htc *htc,
			       u8 *buffer,
			       int length,
			       enum ath10k_htc_ep_id src_eid,
			       void *next_lookaheads,
			       int *next_lookaheads_len)
{
	struct ath10k_htc_lookahead_bundle *bundle;
	struct ath10k *ar = htc->ar;
	int status = 0;
	struct ath10k_htc_record *record;
	u8 *orig_buffer;
	int orig_length;
	size_t len;

	orig_buffer = buffer;
	orig_length = length;

	while (length > 0) {
		record = (struct ath10k_htc_record *)buffer;

		if (length < sizeof(record->hdr)) {
			status = -EINVAL;
			break;
		}

		if (record->hdr.len > length) {
			/* no room left in buffer for record */
			ath10k_warn(ar, "Invalid record length: %d\n",
				    record->hdr.len);
			status = -EINVAL;
			break;
		}

		switch (record->hdr.id) {
		case ATH10K_HTC_RECORD_CREDITS:
			len = sizeof(struct ath10k_htc_credit_report);
			if (record->hdr.len < len) {
				ath10k_warn(ar, "Credit report too long\n");
				status = -EINVAL;
				break;
			}
			ath10k_htc_process_credit_report(htc,
							 record->credit_report,
							 record->hdr.len,
							 src_eid);
			break;
		case ATH10K_HTC_RECORD_LOOKAHEAD:
			len = sizeof(struct ath10k_htc_lookahead_report);
			if (record->hdr.len < len) {
				ath10k_warn(ar, "Lookahead report too long\n");
				status = -EINVAL;
				break;
			}
			status = ath10k_htc_process_lookahead(htc,
							      record->lookahead_report,
							      record->hdr.len,
							      src_eid,
							      next_lookaheads,
							      next_lookaheads_len);
			break;
		case ATH10K_HTC_RECORD_LOOKAHEAD_BUNDLE:
			bundle = record->lookahead_bundle;
			status = ath10k_htc_process_lookahead_bundle(htc,
								     bundle,
								     record->hdr.len,
								     src_eid,
								     next_lookaheads,
								     next_lookaheads_len);
			break;
		default:
			ath10k_warn(ar, "Unhandled record: id:%d length:%d\n",
				    record->hdr.id, record->hdr.len);
			break;
		}

		if (status)
			break;

		/* multiple records may be present in a trailer */
		buffer += sizeof(record->hdr) + record->hdr.len;
		length -= sizeof(record->hdr) + record->hdr.len;
	}

	if (status)
		ath10k_dbg_dump(ar, ATH10K_DBG_HTC, "htc rx bad trailer", "",
				orig_buffer, orig_length);

	return status;
}
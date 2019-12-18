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
struct htc_target {int dummy; } ;
struct htc_record_hdr {int len; int rec_id; } ;
struct htc_credit_report {int dummy; } ;
typedef  enum htc_endpoint_id { ____Placeholder_htc_endpoint_id } htc_endpoint_id ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_HTC ; 
 int EINVAL ; 
#define  HTC_RECORD_CREDITS 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  htc_process_credit_report (struct htc_target*,struct htc_credit_report*,int,int) ; 

__attribute__((used)) static int htc_process_trailer(struct htc_target *target, u8 *buffer,
			       int len, enum htc_endpoint_id from_ep)
{
	struct htc_credit_report *report;
	struct htc_record_hdr *record;
	u8 *record_buf;
	int status = 0;

	while (len > 0) {
		if (len < sizeof(struct htc_record_hdr)) {
			status = -EINVAL;
			break;
		}

		/* these are byte aligned structs */
		record = (struct htc_record_hdr *) buffer;
		len -= sizeof(struct htc_record_hdr);
		buffer += sizeof(struct htc_record_hdr);

		if (record->len > len) {
			/* no room left in buffer for record */
			ath6kl_dbg(ATH6KL_DBG_HTC,
				   "invalid length: %d (id:%d) buffer has: %d bytes left\n",
				   record->len, record->rec_id, len);
			status = -EINVAL;
			break;
		}

		/* start of record follows the header */
		record_buf = buffer;

		switch (record->rec_id) {
		case HTC_RECORD_CREDITS:
			if (record->len < sizeof(struct htc_credit_report)) {
				WARN_ON_ONCE(1);
				return -EINVAL;
			}

			report = (struct htc_credit_report *) record_buf;
			htc_process_credit_report(target, report,
						  record->len / sizeof(*report),
						  from_ep);
			break;
		default:
			ath6kl_dbg(ATH6KL_DBG_HTC,
				   "unhandled record: id:%d length:%d\n",
				   record->rec_id, record->len);
			break;
		}

		/* advance buffer past this record for next time around */
		buffer += record->len;
		len -= record->len;
	}

	return status;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mce {int dummy; } ;
struct TYPE_4__ {int section_count; int record_length; int /*<<< orphan*/  flags; int /*<<< orphan*/  record_id; int /*<<< orphan*/  notification_type; int /*<<< orphan*/  creator_id; scalar_t__ validation_bits; void* error_severity; int /*<<< orphan*/  signature_end; int /*<<< orphan*/  revision; int /*<<< orphan*/ * signature; } ;
struct TYPE_3__ {int section_offset; int section_length; void* section_severity; int /*<<< orphan*/  section_type; int /*<<< orphan*/  flags; scalar_t__ validation_bits; int /*<<< orphan*/  revision; } ;
struct cper_mce_record {TYPE_2__ hdr; int /*<<< orphan*/  mce; TYPE_1__ sec_hdr; } ;
typedef  int /*<<< orphan*/  rcd ;

/* Variables and functions */
 int /*<<< orphan*/  CPER_CREATOR_MCE ; 
 int /*<<< orphan*/  CPER_HW_ERROR_FLAGS_PREVERR ; 
 int /*<<< orphan*/  CPER_NOTIFY_MCE ; 
 int /*<<< orphan*/  CPER_RECORD_REV ; 
 int /*<<< orphan*/  CPER_SECTION_TYPE_MCE ; 
 int /*<<< orphan*/  CPER_SEC_PRIMARY ; 
 int /*<<< orphan*/  CPER_SEC_REV ; 
 void* CPER_SEV_FATAL ; 
 int /*<<< orphan*/  CPER_SIG_END ; 
 struct mce* CPER_SIG_RECORD ; 
 int CPER_SIG_SIZE ; 
 int /*<<< orphan*/  cper_next_record_id () ; 
 int erst_write (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mce*,int) ; 
 int /*<<< orphan*/  memset (struct cper_mce_record*,int /*<<< orphan*/ ,int) ; 

int apei_write_mce(struct mce *m)
{
	struct cper_mce_record rcd;

	memset(&rcd, 0, sizeof(rcd));
	memcpy(rcd.hdr.signature, CPER_SIG_RECORD, CPER_SIG_SIZE);
	rcd.hdr.revision = CPER_RECORD_REV;
	rcd.hdr.signature_end = CPER_SIG_END;
	rcd.hdr.section_count = 1;
	rcd.hdr.error_severity = CPER_SEV_FATAL;
	/* timestamp, platform_id, partition_id are all invalid */
	rcd.hdr.validation_bits = 0;
	rcd.hdr.record_length = sizeof(rcd);
	rcd.hdr.creator_id = CPER_CREATOR_MCE;
	rcd.hdr.notification_type = CPER_NOTIFY_MCE;
	rcd.hdr.record_id = cper_next_record_id();
	rcd.hdr.flags = CPER_HW_ERROR_FLAGS_PREVERR;

	rcd.sec_hdr.section_offset = (void *)&rcd.mce - (void *)&rcd;
	rcd.sec_hdr.section_length = sizeof(rcd.mce);
	rcd.sec_hdr.revision = CPER_SEC_REV;
	/* fru_id and fru_text is invalid */
	rcd.sec_hdr.validation_bits = 0;
	rcd.sec_hdr.flags = CPER_SEC_PRIMARY;
	rcd.sec_hdr.section_type = CPER_SECTION_TYPE_MCE;
	rcd.sec_hdr.section_severity = CPER_SEV_FATAL;

	memcpy(&rcd.mce, m, sizeof(*m));

	return erst_write(&rcd.hdr);
}
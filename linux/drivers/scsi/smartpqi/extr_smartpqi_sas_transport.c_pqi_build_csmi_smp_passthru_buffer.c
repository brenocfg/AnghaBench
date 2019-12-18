#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  sas_address; int /*<<< orphan*/  phy_identifier; } ;
struct sas_rphy {TYPE_1__ identify; } ;
struct TYPE_6__ {int payload_len; int /*<<< orphan*/  sg_cnt; } ;
struct TYPE_5__ {int payload_len; int /*<<< orphan*/  sg_list; } ;
struct bsg_job {TYPE_3__ reply_payload; TYPE_2__ request_payload; } ;
struct bmic_csmi_smp_passthru {int /*<<< orphan*/  request; int /*<<< orphan*/  response_length; int /*<<< orphan*/  request_length; int /*<<< orphan*/  destination_sas_address; scalar_t__ connection_rate; scalar_t__ port_identifier; int /*<<< orphan*/  phy_identifier; } ;
struct bmic_csmi_ioctl_header {int /*<<< orphan*/  length; int /*<<< orphan*/  control_code; int /*<<< orphan*/  timeout; int /*<<< orphan*/  header_length; } ;
struct bmic_csmi_smp_passthru_buffer {struct bmic_csmi_smp_passthru parameters; struct bmic_csmi_ioctl_header ioctl_header; } ;

/* Variables and functions */
 int CSMI_CC_SAS_SMP_PASSTHRU ; 
 int CSMI_IOCTL_TIMEOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SMP_CRC_FIELD_LENGTH ; 
 struct bmic_csmi_smp_passthru_buffer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_be64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct bmic_csmi_smp_passthru_buffer *
pqi_build_csmi_smp_passthru_buffer(struct sas_rphy *rphy,
	struct bsg_job *job)
{
	struct bmic_csmi_smp_passthru_buffer *smp_buf;
	struct bmic_csmi_ioctl_header *ioctl_header;
	struct bmic_csmi_smp_passthru *parameters;
	u32 req_size;
	u32 resp_size;

	smp_buf = kzalloc(sizeof(*smp_buf), GFP_KERNEL);
	if (!smp_buf)
		return NULL;

	req_size = job->request_payload.payload_len;
	resp_size = job->reply_payload.payload_len;

	ioctl_header = &smp_buf->ioctl_header;
	put_unaligned_le32(sizeof(smp_buf->ioctl_header),
		&ioctl_header->header_length);
	put_unaligned_le32(CSMI_IOCTL_TIMEOUT, &ioctl_header->timeout);
	put_unaligned_le32(CSMI_CC_SAS_SMP_PASSTHRU,
		&ioctl_header->control_code);
	put_unaligned_le32(sizeof(smp_buf->parameters), &ioctl_header->length);

	parameters = &smp_buf->parameters;
	parameters->phy_identifier = rphy->identify.phy_identifier;
	parameters->port_identifier = 0;
	parameters->connection_rate = 0;
	put_unaligned_be64(rphy->identify.sas_address,
		&parameters->destination_sas_address);

	if (req_size > SMP_CRC_FIELD_LENGTH)
		req_size -= SMP_CRC_FIELD_LENGTH;

	put_unaligned_le32(req_size, &parameters->request_length);

	put_unaligned_le32(resp_size, &parameters->response_length);

	sg_copy_to_buffer(job->request_payload.sg_list,
		job->reply_payload.sg_cnt, &parameters->request,
		req_size);

	return smp_buf;
}
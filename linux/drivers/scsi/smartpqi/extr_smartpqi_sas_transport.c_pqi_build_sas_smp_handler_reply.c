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
struct pqi_raid_error_info {int /*<<< orphan*/  data_in_transferred; int /*<<< orphan*/  sense_data_length; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {unsigned int payload_len; int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct bsg_job {TYPE_1__ reply_payload; int /*<<< orphan*/  reply; int /*<<< orphan*/  reply_len; } ;
struct TYPE_4__ {int /*<<< orphan*/  response_length; int /*<<< orphan*/  response; } ;
struct bmic_csmi_smp_passthru_buffer {TYPE_2__ parameters; } ;

/* Variables and functions */
 unsigned int get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_copy_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int pqi_build_sas_smp_handler_reply(
	struct bmic_csmi_smp_passthru_buffer *smp_buf, struct bsg_job *job,
	struct pqi_raid_error_info *error_info)
{
	sg_copy_from_buffer(job->reply_payload.sg_list,
		job->reply_payload.sg_cnt, &smp_buf->parameters.response,
		le32_to_cpu(smp_buf->parameters.response_length));

	job->reply_len = le16_to_cpu(error_info->sense_data_length);
	memcpy(job->reply, error_info->data,
			le16_to_cpu(error_info->sense_data_length));

	return job->reply_payload.payload_len -
		get_unaligned_le32(&error_info->data_in_transferred);
}
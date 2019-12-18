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
typedef  scalar_t__ u32 ;
struct be_mcc_wrb {int /*<<< orphan*/  member_0; } ;
struct be_cmd_resp_get_fat {scalar_t__ log_size; } ;
struct be_cmd_req_get_fat {int /*<<< orphan*/  fat_operation; int /*<<< orphan*/  hdr; } ;
struct be_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int /*<<< orphan*/  OPCODE_COMMON_MANAGE_FAT ; 
 int /*<<< orphan*/  QUERY_FAT ; 
 int be_cmd_notify_wait (struct be_adapter*,struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct be_mcc_wrb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* embedded_payload (struct be_mcc_wrb*) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 

int be_cmd_get_fat_dump_len(struct be_adapter *adapter, u32 *dump_size)
{
	struct be_mcc_wrb wrb = {0};
	struct be_cmd_req_get_fat *req;
	int status;

	req = embedded_payload(&wrb);

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			       OPCODE_COMMON_MANAGE_FAT, sizeof(*req),
			       &wrb, NULL);
	req->fat_operation = cpu_to_le32(QUERY_FAT);
	status = be_cmd_notify_wait(adapter, &wrb);
	if (!status) {
		struct be_cmd_resp_get_fat *resp = embedded_payload(&wrb);

		if (dump_size && resp->log_size)
			*dump_size = le32_to_cpu(resp->log_size) -
					sizeof(u32);
	}
	return status;
}
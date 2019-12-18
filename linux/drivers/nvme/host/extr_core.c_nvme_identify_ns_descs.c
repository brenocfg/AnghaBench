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
struct nvme_ns_ids {int /*<<< orphan*/  uuid; int /*<<< orphan*/  nguid; int /*<<< orphan*/  eui64; } ;
struct nvme_ns_id_desc {scalar_t__ nidl; int nidt; } ;
struct nvme_ctrl {int /*<<< orphan*/  device; int /*<<< orphan*/  admin_q; } ;
struct TYPE_2__ {int /*<<< orphan*/  cns; int /*<<< orphan*/  nsid; int /*<<< orphan*/  opcode; } ;
struct nvme_command {TYPE_1__ identify; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NVME_IDENTIFY_DATA_SIZE ; 
 int /*<<< orphan*/  NVME_ID_CNS_NS_DESC_LIST ; 
#define  NVME_NIDT_EUI64 130 
 int NVME_NIDT_EUI64_LEN ; 
#define  NVME_NIDT_NGUID 129 
 int NVME_NIDT_NGUID_LEN ; 
#define  NVME_NIDT_UUID 128 
 int NVME_NIDT_UUID_LEN ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  nvme_admin_identify ; 
 int nvme_submit_sync_cmd (int /*<<< orphan*/ ,struct nvme_command*,void*,int) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int nvme_identify_ns_descs(struct nvme_ctrl *ctrl, unsigned nsid,
		struct nvme_ns_ids *ids)
{
	struct nvme_command c = { };
	int status;
	void *data;
	int pos;
	int len;

	c.identify.opcode = nvme_admin_identify;
	c.identify.nsid = cpu_to_le32(nsid);
	c.identify.cns = NVME_ID_CNS_NS_DESC_LIST;

	data = kzalloc(NVME_IDENTIFY_DATA_SIZE, GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	status = nvme_submit_sync_cmd(ctrl->admin_q, &c, data,
				      NVME_IDENTIFY_DATA_SIZE);
	if (status)
		goto free_data;

	for (pos = 0; pos < NVME_IDENTIFY_DATA_SIZE; pos += len) {
		struct nvme_ns_id_desc *cur = data + pos;

		if (cur->nidl == 0)
			break;

		switch (cur->nidt) {
		case NVME_NIDT_EUI64:
			if (cur->nidl != NVME_NIDT_EUI64_LEN) {
				dev_warn(ctrl->device,
					 "ctrl returned bogus length: %d for NVME_NIDT_EUI64\n",
					 cur->nidl);
				goto free_data;
			}
			len = NVME_NIDT_EUI64_LEN;
			memcpy(ids->eui64, data + pos + sizeof(*cur), len);
			break;
		case NVME_NIDT_NGUID:
			if (cur->nidl != NVME_NIDT_NGUID_LEN) {
				dev_warn(ctrl->device,
					 "ctrl returned bogus length: %d for NVME_NIDT_NGUID\n",
					 cur->nidl);
				goto free_data;
			}
			len = NVME_NIDT_NGUID_LEN;
			memcpy(ids->nguid, data + pos + sizeof(*cur), len);
			break;
		case NVME_NIDT_UUID:
			if (cur->nidl != NVME_NIDT_UUID_LEN) {
				dev_warn(ctrl->device,
					 "ctrl returned bogus length: %d for NVME_NIDT_UUID\n",
					 cur->nidl);
				goto free_data;
			}
			len = NVME_NIDT_UUID_LEN;
			uuid_copy(&ids->uuid, data + pos + sizeof(*cur));
			break;
		default:
			/* Skip unknown types */
			len = cur->nidl;
			break;
		}

		len += sizeof(*cur);
	}
free_data:
	kfree(data);
	return status;
}
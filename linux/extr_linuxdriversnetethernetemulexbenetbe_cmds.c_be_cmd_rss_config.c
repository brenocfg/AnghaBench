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
typedef  int /*<<< orphan*/  const u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct be_mcc_wrb {int dummy; } ;
struct TYPE_2__ {int version; } ;
struct be_cmd_req_rss_config {int /*<<< orphan*/  hash; int /*<<< orphan*/  cpu_table; TYPE_1__ hdr; void* cpu_table_size_log2; void* enable_rss; int /*<<< orphan*/  if_id; } ;
struct be_adapter {int /*<<< orphan*/  mcc_lock; int /*<<< orphan*/  if_handle; } ;

/* Variables and functions */
 int BE_IF_FLAGS_RSS ; 
 int /*<<< orphan*/  BEx_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_ETH ; 
 int EBUSY ; 
 int /*<<< orphan*/  OPCODE_ETH_RSS_CONFIG ; 
 int /*<<< orphan*/  RSS_HASH_KEY_LEN ; 
 int /*<<< orphan*/  be_dws_cpu_to_le (int /*<<< orphan*/ ,int) ; 
 int be_if_cap_flags (struct be_adapter*) ; 
 int be_mcc_notify_wait (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct be_mcc_wrb*,int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct be_cmd_req_rss_config* embedded_payload (struct be_mcc_wrb*) ; 
 scalar_t__ fls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct be_adapter*) ; 

int be_cmd_rss_config(struct be_adapter *adapter, u8 *rsstable,
		      u32 rss_hash_opts, u16 table_size, const u8 *rss_hkey)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_rss_config *req;
	int status;

	if (!(be_if_cap_flags(adapter) & BE_IF_FLAGS_RSS))
		return 0;

	mutex_lock(&adapter->mcc_lock);

	wrb = wrb_from_mccq(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err;
	}
	req = embedded_payload(wrb);

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ETH,
			       OPCODE_ETH_RSS_CONFIG, sizeof(*req), wrb, NULL);

	req->if_id = cpu_to_le32(adapter->if_handle);
	req->enable_rss = cpu_to_le16(rss_hash_opts);
	req->cpu_table_size_log2 = cpu_to_le16(fls(table_size) - 1);

	if (!BEx_chip(adapter))
		req->hdr.version = 1;

	memcpy(req->cpu_table, rsstable, table_size);
	memcpy(req->hash, rss_hkey, RSS_HASH_KEY_LEN);
	be_dws_cpu_to_le(req->hash, sizeof(req->hash));

	status = be_mcc_notify_wait(adapter);
err:
	mutex_unlock(&adapter->mcc_lock);
	return status;
}
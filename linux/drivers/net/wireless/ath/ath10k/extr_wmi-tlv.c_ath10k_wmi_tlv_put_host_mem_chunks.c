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
struct wmi_tlv {scalar_t__ value; void* len; void* tag; } ;
struct host_memory_chunk {void* req_id; void* size; void* ptr; } ;
struct TYPE_4__ {int num_mem_chunks; TYPE_1__* mem_chunks; } ;
struct ath10k {TYPE_2__ wmi; } ;
typedef  void* __le16 ;
struct TYPE_3__ {scalar_t__ req_id; scalar_t__ paddr; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int WMI_TLV_TAG_STRUCT_WLAN_HOST_MEMORY_CHUNK ; 
 void* __cpu_to_le16 (int) ; 
 void* __cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int,scalar_t__,unsigned long long,scalar_t__) ; 

__attribute__((used)) static void
ath10k_wmi_tlv_put_host_mem_chunks(struct ath10k *ar, void *host_mem_chunks)
{
	struct host_memory_chunk *chunk;
	struct wmi_tlv *tlv;
	int i;
	__le16 tlv_len, tlv_tag;

	tlv_tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_WLAN_HOST_MEMORY_CHUNK);
	tlv_len = __cpu_to_le16(sizeof(*chunk));
	for (i = 0; i < ar->wmi.num_mem_chunks; i++) {
		tlv = host_mem_chunks;
		tlv->tag = tlv_tag;
		tlv->len = tlv_len;
		chunk = (void *)tlv->value;

		chunk->ptr = __cpu_to_le32(ar->wmi.mem_chunks[i].paddr);
		chunk->size = __cpu_to_le32(ar->wmi.mem_chunks[i].len);
		chunk->req_id = __cpu_to_le32(ar->wmi.mem_chunks[i].req_id);

		ath10k_dbg(ar, ATH10K_DBG_WMI,
			   "wmi-tlv chunk %d len %d, addr 0x%llx, id 0x%x\n",
			   i,
			   ar->wmi.mem_chunks[i].len,
			   (unsigned long long)ar->wmi.mem_chunks[i].paddr,
			   ar->wmi.mem_chunks[i].req_id);

		host_mem_chunks += sizeof(*tlv);
		host_mem_chunks += sizeof(*chunk);
	}
}
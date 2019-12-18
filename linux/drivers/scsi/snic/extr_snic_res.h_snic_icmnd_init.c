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
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {void* sense_addr; void* sense_len; void* sg_addr; void* data_len; int /*<<< orphan*/ * cdb; int /*<<< orphan*/  cdb_len; int /*<<< orphan*/  lun_id; void* tgt_id; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__ icmnd; } ;
struct snic_host_req {TYPE_2__ u; int /*<<< orphan*/  hdr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  LUN_ADDR_LEN ; 
 int /*<<< orphan*/  SNIC_CDB_LEN ; 
 int /*<<< orphan*/  SNIC_REQ_ICMND ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snic_io_hdr_enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
snic_icmnd_init(struct snic_host_req *req, u32 cmnd_id, u32 host_id, u64 ctx,
		u16 flags, u64 tgt_id, u8 *lun, u8 *scsi_cdb, u8 cdb_len,
		u32 data_len, u16 sg_cnt, ulong sgl_addr,
		dma_addr_t sns_addr_pa, u32 sense_len)
{
	snic_io_hdr_enc(&req->hdr, SNIC_REQ_ICMND, 0, cmnd_id, host_id, sg_cnt,
			ctx);

	req->u.icmnd.flags = cpu_to_le16(flags);
	req->u.icmnd.tgt_id = cpu_to_le64(tgt_id);
	memcpy(&req->u.icmnd.lun_id, lun, LUN_ADDR_LEN);
	req->u.icmnd.cdb_len = cdb_len;
	memset(req->u.icmnd.cdb, 0, SNIC_CDB_LEN);
	memcpy(req->u.icmnd.cdb, scsi_cdb, cdb_len);
	req->u.icmnd.data_len = cpu_to_le32(data_len);
	req->u.icmnd.sg_addr = cpu_to_le64(sgl_addr);
	req->u.icmnd.sense_len = cpu_to_le32(sense_len);
	req->u.icmnd.sense_addr = cpu_to_le64(sns_addr_pa);
}
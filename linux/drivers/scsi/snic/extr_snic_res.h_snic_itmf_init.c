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
struct TYPE_3__ {int /*<<< orphan*/  lun_id; int /*<<< orphan*/  tgt_id; int /*<<< orphan*/  req_id; int /*<<< orphan*/  flags; int /*<<< orphan*/  tm_type; } ;
struct TYPE_4__ {TYPE_1__ itmf; } ;
struct snic_host_req {TYPE_2__ u; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUN_ADDR_LEN ; 
 int /*<<< orphan*/  SNIC_REQ_ITMF ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snic_io_hdr_enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
snic_itmf_init(struct snic_host_req *req, u32 cmnd_id, u32 host_id, ulong ctx,
	       u16 flags, u32 req_id, u64 tgt_id, u8 *lun, u8 tm_type)
{
	snic_io_hdr_enc(&req->hdr, SNIC_REQ_ITMF, 0, cmnd_id, host_id, 0, ctx);

	req->u.itmf.tm_type = tm_type;
	req->u.itmf.flags = cpu_to_le16(flags);
	/* req_id valid only in abort, clear task */
	req->u.itmf.req_id = cpu_to_le32(req_id);
	req->u.itmf.tgt_id = cpu_to_le64(tgt_id);
	memcpy(&req->u.itmf.lun_id, lun, LUN_ADDR_LEN);
}
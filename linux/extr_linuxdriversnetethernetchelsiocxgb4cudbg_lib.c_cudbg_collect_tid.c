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
typedef  void* u32 ;
struct cudbg_ver_hdr {int dummy; } ;
struct TYPE_4__ {int size; int /*<<< orphan*/  revision; int /*<<< orphan*/  signature; } ;
struct cudbg_tid_info_region {int sb; int le_db_conf; int ip_users; int ipv6_users; int /*<<< orphan*/  flags; int /*<<< orphan*/  nsftids; int /*<<< orphan*/  sftid_base; int /*<<< orphan*/  aftid_end; int /*<<< orphan*/  aftid_base; int /*<<< orphan*/  ftid_base; int /*<<< orphan*/  nftids; int /*<<< orphan*/  natids; int /*<<< orphan*/  hash_base; int /*<<< orphan*/  stid_base; int /*<<< orphan*/  nstids; int /*<<< orphan*/  ntids; void* nhpftids; void* hpftid_base; void* nuotids; void* uotid_base; } ;
struct cudbg_tid_info_region_rev1 {int tid_start; TYPE_1__ ver_hdr; struct cudbg_tid_info_region tid; } ;
struct cudbg_init {struct adapter* adap; } ;
struct cudbg_error {int sys_err; } ;
struct cudbg_buffer {scalar_t__ data; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int /*<<< orphan*/  nsftids; int /*<<< orphan*/  sftid_base; int /*<<< orphan*/  aftid_end; int /*<<< orphan*/  aftid_base; int /*<<< orphan*/  ftid_base; int /*<<< orphan*/  nftids; int /*<<< orphan*/  natids; int /*<<< orphan*/  hash_base; int /*<<< orphan*/  stid_base; int /*<<< orphan*/  nstids; int /*<<< orphan*/  ntids; } ;
struct TYPE_5__ {int /*<<< orphan*/  chip; } ;
struct adapter {int /*<<< orphan*/  flags; TYPE_3__ tids; int /*<<< orphan*/  pf; int /*<<< orphan*/  mbox; TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CUDBG_ENTITY_SIGNATURE ; 
 int /*<<< orphan*/  CUDBG_TID_INFO_REV ; 
 int /*<<< orphan*/  FW_PARAMS_MNEM_PFVF ; 
 int FW_PARAMS_MNEM_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_PFVF_ETHOFLD_END ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_PFVF_ETHOFLD_START ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_PFVF_HPFILTER_END ; 
 int /*<<< orphan*/  FW_PARAMS_PARAM_PFVF_HPFILTER_START ; 
 int FW_PARAMS_PARAM_X_V (int /*<<< orphan*/ ) ; 
 int FW_PARAMS_PARAM_Y_V (int /*<<< orphan*/ ) ; 
 int FW_PARAMS_PARAM_Z_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LE_DB_ACTIVE_TABLE_START_INDEX_A ; 
 int /*<<< orphan*/  LE_DB_ACT_CNT_IPV4_A ; 
 int /*<<< orphan*/  LE_DB_ACT_CNT_IPV6_A ; 
 int /*<<< orphan*/  LE_DB_CONFIG_A ; 
 int /*<<< orphan*/  LE_DB_SERVER_INDEX_A ; 
 int /*<<< orphan*/  LE_DB_SRVR_START_INDEX_A ; 
 int cudbg_get_buff (struct cudbg_init*,struct cudbg_buffer*,int,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  cudbg_put_buff (struct cudbg_init*,struct cudbg_buffer*) ; 
 int cudbg_write_and_release_buff (struct cudbg_init*,struct cudbg_buffer*,struct cudbg_buffer*) ; 
 int /*<<< orphan*/  is_fw_attached (struct cudbg_init*) ; 
 scalar_t__ is_t5 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_t6 (int /*<<< orphan*/ ) ; 
 int t4_query_params (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void**,void**) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

int cudbg_collect_tid(struct cudbg_init *pdbg_init,
		      struct cudbg_buffer *dbg_buff,
		      struct cudbg_error *cudbg_err)
{
	struct adapter *padap = pdbg_init->adap;
	struct cudbg_tid_info_region_rev1 *tid1;
	struct cudbg_buffer temp_buff = { 0 };
	struct cudbg_tid_info_region *tid;
	u32 para[2], val[2];
	int rc;

	rc = cudbg_get_buff(pdbg_init, dbg_buff,
			    sizeof(struct cudbg_tid_info_region_rev1),
			    &temp_buff);
	if (rc)
		return rc;

	tid1 = (struct cudbg_tid_info_region_rev1 *)temp_buff.data;
	tid = &tid1->tid;
	tid1->ver_hdr.signature = CUDBG_ENTITY_SIGNATURE;
	tid1->ver_hdr.revision = CUDBG_TID_INFO_REV;
	tid1->ver_hdr.size = sizeof(struct cudbg_tid_info_region_rev1) -
			     sizeof(struct cudbg_ver_hdr);

	/* If firmware is not attached/alive, use backdoor register
	 * access to collect dump.
	 */
	if (!is_fw_attached(pdbg_init))
		goto fill_tid;

#define FW_PARAM_PFVF_A(param) \
	(FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_PFVF) | \
	 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_PFVF_##param) | \
	 FW_PARAMS_PARAM_Y_V(0) | \
	 FW_PARAMS_PARAM_Z_V(0))

	para[0] = FW_PARAM_PFVF_A(ETHOFLD_START);
	para[1] = FW_PARAM_PFVF_A(ETHOFLD_END);
	rc = t4_query_params(padap, padap->mbox, padap->pf, 0, 2, para, val);
	if (rc <  0) {
		cudbg_err->sys_err = rc;
		cudbg_put_buff(pdbg_init, &temp_buff);
		return rc;
	}
	tid->uotid_base = val[0];
	tid->nuotids = val[1] - val[0] + 1;

	if (is_t5(padap->params.chip)) {
		tid->sb = t4_read_reg(padap, LE_DB_SERVER_INDEX_A) / 4;
	} else if (is_t6(padap->params.chip)) {
		tid1->tid_start =
			t4_read_reg(padap, LE_DB_ACTIVE_TABLE_START_INDEX_A);
		tid->sb = t4_read_reg(padap, LE_DB_SRVR_START_INDEX_A);

		para[0] = FW_PARAM_PFVF_A(HPFILTER_START);
		para[1] = FW_PARAM_PFVF_A(HPFILTER_END);
		rc = t4_query_params(padap, padap->mbox, padap->pf, 0, 2,
				     para, val);
		if (rc < 0) {
			cudbg_err->sys_err = rc;
			cudbg_put_buff(pdbg_init, &temp_buff);
			return rc;
		}
		tid->hpftid_base = val[0];
		tid->nhpftids = val[1] - val[0] + 1;
	}

#undef FW_PARAM_PFVF_A

fill_tid:
	tid->ntids = padap->tids.ntids;
	tid->nstids = padap->tids.nstids;
	tid->stid_base = padap->tids.stid_base;
	tid->hash_base = padap->tids.hash_base;

	tid->natids = padap->tids.natids;
	tid->nftids = padap->tids.nftids;
	tid->ftid_base = padap->tids.ftid_base;
	tid->aftid_base = padap->tids.aftid_base;
	tid->aftid_end = padap->tids.aftid_end;

	tid->sftid_base = padap->tids.sftid_base;
	tid->nsftids = padap->tids.nsftids;

	tid->flags = padap->flags;
	tid->le_db_conf = t4_read_reg(padap, LE_DB_CONFIG_A);
	tid->ip_users = t4_read_reg(padap, LE_DB_ACT_CNT_IPV4_A);
	tid->ipv6_users = t4_read_reg(padap, LE_DB_ACT_CNT_IPV6_A);

	return cudbg_write_and_release_buff(pdbg_init, &temp_buff, dbg_buff);
}
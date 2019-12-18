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
typedef  scalar_t__ u16 ;
struct zfcp_fsf_req {int /*<<< orphan*/  req_id; struct zfcp_fsf_ct_els* data; TYPE_1__* adapter; } ;
struct zfcp_fsf_ct_els {int /*<<< orphan*/  d_id; int /*<<< orphan*/  resp; } ;
struct zfcp_dbf {int /*<<< orphan*/  san; } ;
struct TYPE_2__ {struct zfcp_dbf* dbf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_DBF_SAN_LEVEL ; 
 int /*<<< orphan*/  ZFCP_DBF_SAN_RES ; 
 int /*<<< orphan*/  debug_level_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  zfcp_dbf_san (char*,struct zfcp_dbf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_dbf_san_res_cap_len_if_gpn_ft (char*,struct zfcp_fsf_req*,scalar_t__) ; 
 scalar_t__ zfcp_qdio_real_bytes (int /*<<< orphan*/ ) ; 

void zfcp_dbf_san_res(char *tag, struct zfcp_fsf_req *fsf)
{
	struct zfcp_dbf *dbf = fsf->adapter->dbf;
	struct zfcp_fsf_ct_els *ct_els = fsf->data;
	u16 length;

	if (unlikely(!debug_level_enabled(dbf->san, ZFCP_DBF_SAN_LEVEL)))
		return;

	length = (u16)zfcp_qdio_real_bytes(ct_els->resp);
	zfcp_dbf_san(tag, dbf, "san_res", ct_els->resp, ZFCP_DBF_SAN_RES,
		     length, fsf->req_id, ct_els->d_id,
		     zfcp_dbf_san_res_cap_len_if_gpn_ft(tag, fsf, length));
}
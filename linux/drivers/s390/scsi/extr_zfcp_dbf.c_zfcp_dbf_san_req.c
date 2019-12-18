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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct zfcp_fsf_req {int /*<<< orphan*/  req_id; struct zfcp_fsf_ct_els* data; TYPE_1__* adapter; } ;
struct zfcp_fsf_ct_els {int /*<<< orphan*/  req; } ;
struct zfcp_dbf {int /*<<< orphan*/  san; } ;
struct TYPE_2__ {struct zfcp_dbf* dbf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_DBF_SAN_LEVEL ; 
 int /*<<< orphan*/  ZFCP_DBF_SAN_REQ ; 
 int /*<<< orphan*/  debug_level_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  zfcp_dbf_san (char*,struct zfcp_dbf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ zfcp_qdio_real_bytes (int /*<<< orphan*/ ) ; 

void zfcp_dbf_san_req(char *tag, struct zfcp_fsf_req *fsf, u32 d_id)
{
	struct zfcp_dbf *dbf = fsf->adapter->dbf;
	struct zfcp_fsf_ct_els *ct_els = fsf->data;
	u16 length;

	if (unlikely(!debug_level_enabled(dbf->san, ZFCP_DBF_SAN_LEVEL)))
		return;

	length = (u16)zfcp_qdio_real_bytes(ct_els->req);
	zfcp_dbf_san(tag, dbf, "san_req", ct_els->req, ZFCP_DBF_SAN_REQ,
		     length, fsf->req_id, d_id, length);
}
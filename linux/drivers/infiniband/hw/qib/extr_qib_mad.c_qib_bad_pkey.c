#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  pkey_violations; int /*<<< orphan*/  n_pkt_drops; } ;
struct qib_ibport {TYPE_1__ rvp; } ;
struct TYPE_6__ {void* qp2; void* sl_qp1; void* key; void* lid2; void* lid1; } ;
struct TYPE_8__ {TYPE_2__ ntc_257_258; } ;
struct ib_mad_notice_attr {TYPE_4__ details; scalar_t__ toggle_count; int /*<<< orphan*/  issuer_lid; int /*<<< orphan*/  trap_num; int /*<<< orphan*/  prod_type_lsb; scalar_t__ prod_type_msb; int /*<<< orphan*/  generic_type; } ;
typedef  int /*<<< orphan*/  data ;
typedef  void* __be16 ;
struct TYPE_7__ {int /*<<< orphan*/  lid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_NOTICE_PROD_CA ; 
 int /*<<< orphan*/  IB_NOTICE_TRAP_BAD_PKEY ; 
 int /*<<< orphan*/  IB_NOTICE_TYPE_SECURITY ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* ppd_from_ibp (struct qib_ibport*) ; 
 int /*<<< orphan*/  qib_send_trap (struct qib_ibport*,struct ib_mad_notice_attr*,int) ; 

void qib_bad_pkey(struct qib_ibport *ibp, u32 key, u32 sl,
		  u32 qp1, u32 qp2, __be16 lid1, __be16 lid2)
{
	struct ib_mad_notice_attr data;

	ibp->rvp.n_pkt_drops++;
	ibp->rvp.pkey_violations++;

	/* Send violation trap */
	data.generic_type = IB_NOTICE_TYPE_SECURITY;
	data.prod_type_msb = 0;
	data.prod_type_lsb = IB_NOTICE_PROD_CA;
	data.trap_num = IB_NOTICE_TRAP_BAD_PKEY;
	data.issuer_lid = cpu_to_be16(ppd_from_ibp(ibp)->lid);
	data.toggle_count = 0;
	memset(&data.details, 0, sizeof(data.details));
	data.details.ntc_257_258.lid1 = lid1;
	data.details.ntc_257_258.lid2 = lid2;
	data.details.ntc_257_258.key = cpu_to_be32(key);
	data.details.ntc_257_258.sl_qp1 = cpu_to_be32((sl << 28) | qp1);
	data.details.ntc_257_258.qp2 = cpu_to_be32(qp2);

	qib_send_trap(ibp, &data, sizeof(data));
}
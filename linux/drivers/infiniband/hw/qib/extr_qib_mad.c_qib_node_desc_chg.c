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
struct qib_ibport {int dummy; } ;
struct TYPE_4__ {int local_changes; int /*<<< orphan*/  change_flags; int /*<<< orphan*/  lid; } ;
struct TYPE_6__ {TYPE_1__ ntc_144; } ;
struct ib_mad_notice_attr {TYPE_3__ details; int /*<<< orphan*/  issuer_lid; scalar_t__ toggle_count; int /*<<< orphan*/  trap_num; int /*<<< orphan*/  prod_type_lsb; scalar_t__ prod_type_msb; int /*<<< orphan*/  generic_type; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_5__ {int /*<<< orphan*/  lid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_NOTICE_PROD_CA ; 
 int /*<<< orphan*/  IB_NOTICE_TRAP_CAP_MASK_CHG ; 
 int /*<<< orphan*/  IB_NOTICE_TRAP_NODE_DESC_CHG ; 
 int /*<<< orphan*/  IB_NOTICE_TYPE_INFO ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* ppd_from_ibp (struct qib_ibport*) ; 
 int /*<<< orphan*/  qib_send_trap (struct qib_ibport*,struct ib_mad_notice_attr*,int) ; 

void qib_node_desc_chg(struct qib_ibport *ibp)
{
	struct ib_mad_notice_attr data;

	data.generic_type = IB_NOTICE_TYPE_INFO;
	data.prod_type_msb = 0;
	data.prod_type_lsb = IB_NOTICE_PROD_CA;
	data.trap_num = IB_NOTICE_TRAP_CAP_MASK_CHG;
	data.issuer_lid = cpu_to_be16(ppd_from_ibp(ibp)->lid);
	data.toggle_count = 0;
	memset(&data.details, 0, sizeof(data.details));
	data.details.ntc_144.lid = data.issuer_lid;
	data.details.ntc_144.local_changes = 1;
	data.details.ntc_144.change_flags = IB_NOTICE_TRAP_NODE_DESC_CHG;

	qib_send_trap(ibp, &data, sizeof(data));
}
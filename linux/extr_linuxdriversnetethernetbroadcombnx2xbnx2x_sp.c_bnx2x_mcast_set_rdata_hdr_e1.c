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
typedef  void* u8 ;
struct TYPE_3__ {void* length; int /*<<< orphan*/  echo; int /*<<< orphan*/  client_id; void* offset; } ;
struct mac_configuration_cmd {TYPE_1__ hdr; } ;
struct bnx2x_raw_obj {int func_id; int cid; scalar_t__ rdata; } ;
struct bnx2x_mcast_ramrod_params {TYPE_2__* mcast_obj; } ;
struct bnx2x {int dummy; } ;
struct TYPE_4__ {struct bnx2x_raw_obj raw; } ;

/* Variables and functions */
 int BNX2X_FILTER_MCAST_PENDING ; 
 int BNX2X_MAX_EMUL_MULTI ; 
 int BNX2X_MAX_MULTICAST ; 
 int BNX2X_SWCID_MASK ; 
 int BNX2X_SWCID_SHIFT ; 
 scalar_t__ CHIP_REV_IS_SLOW (struct bnx2x*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static inline void bnx2x_mcast_set_rdata_hdr_e1(struct bnx2x *bp,
					struct bnx2x_mcast_ramrod_params *p,
					u8 len)
{
	struct bnx2x_raw_obj *r = &p->mcast_obj->raw;
	struct mac_configuration_cmd *data =
		(struct mac_configuration_cmd *)(r->rdata);

	u8 offset = (CHIP_REV_IS_SLOW(bp) ?
		     BNX2X_MAX_EMUL_MULTI*(1 + r->func_id) :
		     BNX2X_MAX_MULTICAST*(1 + r->func_id));

	data->hdr.offset = offset;
	data->hdr.client_id = cpu_to_le16(0xff);
	data->hdr.echo = cpu_to_le32((r->cid & BNX2X_SWCID_MASK) |
				     (BNX2X_FILTER_MCAST_PENDING <<
				      BNX2X_SWCID_SHIFT));
	data->hdr.length = len;
}
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
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  interface_id; int /*<<< orphan*/  subnet_prefix; } ;
struct TYPE_6__ {TYPE_2__ global; } ;
struct ib_grh {int /*<<< orphan*/  dgid; TYPE_3__ sgid; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  next_hdr; int /*<<< orphan*/  paylen; int /*<<< orphan*/  version_tclass_flow; } ;
struct ib_global_route {int traffic_class; int flow_label; scalar_t__ sgid_index; int /*<<< orphan*/  dgid; int /*<<< orphan*/  hop_limit; } ;
struct TYPE_4__ {int /*<<< orphan*/  gid_prefix; } ;
struct hfi1_ibport {TYPE_1__ rvp; } ;

/* Variables and functions */
 scalar_t__ HFI1_GUIDS_PER_PORT ; 
 scalar_t__ HFI1_PORT_GUID_INDEX ; 
 int IB_GRH_FLOW_SHIFT ; 
 int /*<<< orphan*/  IB_GRH_NEXT_HDR ; 
 int IB_GRH_TCLASS_SHIFT ; 
 int IB_GRH_VERSION ; 
 int IB_GRH_VERSION_SHIFT ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  get_sguid (struct hfi1_ibport*,scalar_t__) ; 

u32 hfi1_make_grh(struct hfi1_ibport *ibp, struct ib_grh *hdr,
		  const struct ib_global_route *grh, u32 hwords, u32 nwords)
{
	hdr->version_tclass_flow =
		cpu_to_be32((IB_GRH_VERSION << IB_GRH_VERSION_SHIFT) |
			    (grh->traffic_class << IB_GRH_TCLASS_SHIFT) |
			    (grh->flow_label << IB_GRH_FLOW_SHIFT));
	hdr->paylen = cpu_to_be16((hwords + nwords) << 2);
	/* next_hdr is defined by C8-7 in ch. 8.4.1 */
	hdr->next_hdr = IB_GRH_NEXT_HDR;
	hdr->hop_limit = grh->hop_limit;
	/* The SGID is 32-bit aligned. */
	hdr->sgid.global.subnet_prefix = ibp->rvp.gid_prefix;
	hdr->sgid.global.interface_id =
		grh->sgid_index < HFI1_GUIDS_PER_PORT ?
		get_sguid(ibp, grh->sgid_index) :
		get_sguid(ibp, HFI1_PORT_GUID_INDEX);
	hdr->dgid = grh->dgid;

	/* GRH header size in 32-bit words. */
	return sizeof(struct ib_grh) / sizeof(u32);
}
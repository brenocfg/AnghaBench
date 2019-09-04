#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct mthca_dev {int dummy; } ;
struct TYPE_9__ {TYPE_2__* sgid_attr; } ;
struct mthca_ah {scalar_t__ type; TYPE_6__* av; TYPE_3__ ibah; } ;
struct TYPE_10__ {int /*<<< orphan*/  raw; } ;
struct TYPE_11__ {int traffic_class; int flow_label; TYPE_4__ destination_gid; int /*<<< orphan*/  source_gid; int /*<<< orphan*/  hop_limit; } ;
struct TYPE_7__ {int service_level; int /*<<< orphan*/  source_lid; int /*<<< orphan*/  destination_lid; } ;
struct ib_ud_header {TYPE_5__ grh; TYPE_1__ lrh; } ;
struct TYPE_12__ {int sl_tclass_flowlabel; int g_slid; int /*<<< orphan*/  dgid; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  dlid; } ;
struct TYPE_8__ {int /*<<< orphan*/  gid; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MTHCA_AH_ON_HCA ; 
 int be32_to_cpu (int) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mthca_ah_grh_present (struct mthca_ah*) ; 

int mthca_read_ah(struct mthca_dev *dev, struct mthca_ah *ah,
		  struct ib_ud_header *header)
{
	if (ah->type == MTHCA_AH_ON_HCA)
		return -EINVAL;

	header->lrh.service_level   = be32_to_cpu(ah->av->sl_tclass_flowlabel) >> 28;
	header->lrh.destination_lid = ah->av->dlid;
	header->lrh.source_lid      = cpu_to_be16(ah->av->g_slid & 0x7f);
	if (mthca_ah_grh_present(ah)) {
		header->grh.traffic_class =
			(be32_to_cpu(ah->av->sl_tclass_flowlabel) >> 20) & 0xff;
		header->grh.flow_label    =
			ah->av->sl_tclass_flowlabel & cpu_to_be32(0xfffff);
		header->grh.hop_limit     = ah->av->hop_limit;
		header->grh.source_gid = ah->ibah.sgid_attr->gid;
		memcpy(header->grh.destination_gid.raw,
		       ah->av->dgid, 16);
	}

	return 0;
}
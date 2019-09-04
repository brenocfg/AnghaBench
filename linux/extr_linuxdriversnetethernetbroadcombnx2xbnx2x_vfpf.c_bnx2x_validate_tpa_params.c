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
struct TYPE_2__ {scalar_t__ max_sges_for_packet; scalar_t__ max_tpa_queues; } ;
struct vfpf_tpa_tlv {TYPE_1__ tpa_client_info; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,scalar_t__,scalar_t__) ; 
 int EINVAL ; 
 scalar_t__ MAX_AGG_QS (struct bnx2x*) ; 
 scalar_t__ U_ETH_MAX_SGES_FOR_PACKET ; 

__attribute__((used)) static int bnx2x_validate_tpa_params(struct bnx2x *bp,
				       struct vfpf_tpa_tlv *tpa_tlv)
{
	int rc = 0;

	if (tpa_tlv->tpa_client_info.max_sges_for_packet >
	    U_ETH_MAX_SGES_FOR_PACKET) {
		rc = -EINVAL;
		BNX2X_ERR("TPA update: max_sges received %d, max is %d\n",
			  tpa_tlv->tpa_client_info.max_sges_for_packet,
			  U_ETH_MAX_SGES_FOR_PACKET);
	}

	if (tpa_tlv->tpa_client_info.max_tpa_queues > MAX_AGG_QS(bp)) {
		rc = -EINVAL;
		BNX2X_ERR("TPA update: max_tpa_queues received %d, max is %d\n",
			  tpa_tlv->tpa_client_info.max_tpa_queues,
			  MAX_AGG_QS(bp));
	}

	return rc;
}
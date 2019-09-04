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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {scalar_t__ eth_fp_hsi_minor; int capabilities; } ;
struct TYPE_4__ {TYPE_1__ vfdev_info; } ;
struct qed_vf_info {TYPE_2__ acquire; } ;

/* Variables and functions */
 scalar_t__ ETH_HSI_VER_NO_PKT_LEN_TUNN ; 
 int /*<<< orphan*/  QED_QCID_LEGACY_VF_CID ; 
 int /*<<< orphan*/  QED_QCID_LEGACY_VF_RX_PROD ; 
 int VFPF_ACQUIRE_CAP_QUEUE_QIDS ; 

__attribute__((used)) static u8 qed_vf_calculate_legacy(struct qed_vf_info *p_vf)
{
	u8 legacy = 0;

	if (p_vf->acquire.vfdev_info.eth_fp_hsi_minor ==
	    ETH_HSI_VER_NO_PKT_LEN_TUNN)
		legacy |= QED_QCID_LEGACY_VF_RX_PROD;

	if (!(p_vf->acquire.vfdev_info.capabilities &
	      VFPF_ACQUIRE_CAP_QUEUE_QIDS))
		legacy |= QED_QCID_LEGACY_VF_CID;

	return legacy;
}
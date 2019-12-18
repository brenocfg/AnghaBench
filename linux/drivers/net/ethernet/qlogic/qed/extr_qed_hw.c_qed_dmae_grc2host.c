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
typedef  int u32 ;
struct qed_ptt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct qed_hwfn {TYPE_1__ dmae_info; } ;
struct qed_dmae_params {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  QED_DMAE_ADDRESS_GRC ; 
 int /*<<< orphan*/  QED_DMAE_ADDRESS_HOST_VIRT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int qed_dmae_execute_command (struct qed_hwfn*,struct qed_ptt*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct qed_dmae_params*) ; 

int qed_dmae_grc2host(struct qed_hwfn *p_hwfn,
		      struct qed_ptt *p_ptt,
		      u32 grc_addr,
		      dma_addr_t dest_addr, u32 size_in_dwords,
		      struct qed_dmae_params *p_params)
{
	u32 grc_addr_in_dw = grc_addr / sizeof(u32);
	int rc;


	mutex_lock(&p_hwfn->dmae_info.mutex);

	rc = qed_dmae_execute_command(p_hwfn, p_ptt, grc_addr_in_dw,
				      dest_addr, QED_DMAE_ADDRESS_GRC,
				      QED_DMAE_ADDRESS_HOST_VIRT,
				      size_in_dwords, p_params);

	mutex_unlock(&p_hwfn->dmae_info.mutex);

	return rc;
}
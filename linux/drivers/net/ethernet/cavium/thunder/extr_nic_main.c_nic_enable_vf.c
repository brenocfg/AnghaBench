#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nicpf {int* vf_enabled; int num_vf_en; int /*<<< orphan*/  node; int /*<<< orphan*/ * vf_lmac_map; } ;

/* Variables and functions */
 int NIC_GET_BGX_FROM_VF_LMAC_MAP (int /*<<< orphan*/ ) ; 
 int NIC_GET_LMAC_FROM_VF_LMAC_MAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgx_lmac_rx_tx_enable (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void nic_enable_vf(struct nicpf *nic, int vf, bool enable)
{
	int bgx, lmac;

	nic->vf_enabled[vf] = enable;

	if (vf >= nic->num_vf_en)
		return;

	bgx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);
	lmac = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[vf]);

	bgx_lmac_rx_tx_enable(nic->node, bgx, lmac, enable);
}
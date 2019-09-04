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
struct hclge_promisc_param {int vf_id; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_PROMISC_EN_BC ; 
 int /*<<< orphan*/  HCLGE_PROMISC_EN_MC ; 
 int /*<<< orphan*/  HCLGE_PROMISC_EN_UC ; 
 int /*<<< orphan*/  memset (struct hclge_promisc_param*,int /*<<< orphan*/ ,int) ; 

void hclge_promisc_param_init(struct hclge_promisc_param *param, bool en_uc,
			      bool en_mc, bool en_bc, int vport_id)
{
	if (!param)
		return;

	memset(param, 0, sizeof(struct hclge_promisc_param));
	if (en_uc)
		param->enable = HCLGE_PROMISC_EN_UC;
	if (en_mc)
		param->enable |= HCLGE_PROMISC_EN_MC;
	if (en_bc)
		param->enable |= HCLGE_PROMISC_EN_BC;
	param->vf_id = vport_id;
}
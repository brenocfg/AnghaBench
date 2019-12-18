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
struct mtk_mdp_vpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_MDP_DEINIT ; 
 int mtk_mdp_vpu_send_ap_ipi (struct mtk_mdp_vpu*,int /*<<< orphan*/ ) ; 

int mtk_mdp_vpu_deinit(struct mtk_mdp_vpu *vpu)
{
	return mtk_mdp_vpu_send_ap_ipi(vpu, AP_MDP_DEINIT);
}
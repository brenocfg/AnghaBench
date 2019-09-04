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
struct tda998x_priv {int vip_cntrl_0; int vip_cntrl_1; int vip_cntrl_2; int /*<<< orphan*/  audio_params; } ;
struct tda998x_encoder_params {int /*<<< orphan*/  audio_params; scalar_t__ mirr_f; int /*<<< orphan*/  swap_f; scalar_t__ mirr_e; int /*<<< orphan*/  swap_e; scalar_t__ mirr_d; int /*<<< orphan*/  swap_d; scalar_t__ mirr_c; int /*<<< orphan*/  swap_c; scalar_t__ mirr_b; int /*<<< orphan*/  swap_b; scalar_t__ mirr_a; int /*<<< orphan*/  swap_a; } ;

/* Variables and functions */
 int VIP_CNTRL_0_MIRR_A ; 
 int VIP_CNTRL_0_MIRR_B ; 
 int VIP_CNTRL_0_SWAP_A (int /*<<< orphan*/ ) ; 
 int VIP_CNTRL_0_SWAP_B (int /*<<< orphan*/ ) ; 
 int VIP_CNTRL_1_MIRR_C ; 
 int VIP_CNTRL_1_MIRR_D ; 
 int VIP_CNTRL_1_SWAP_C (int /*<<< orphan*/ ) ; 
 int VIP_CNTRL_1_SWAP_D (int /*<<< orphan*/ ) ; 
 int VIP_CNTRL_2_MIRR_E ; 
 int VIP_CNTRL_2_MIRR_F ; 
 int VIP_CNTRL_2_SWAP_E (int /*<<< orphan*/ ) ; 
 int VIP_CNTRL_2_SWAP_F (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tda998x_set_config(struct tda998x_priv *priv,
			       const struct tda998x_encoder_params *p)
{
	priv->vip_cntrl_0 = VIP_CNTRL_0_SWAP_A(p->swap_a) |
			    (p->mirr_a ? VIP_CNTRL_0_MIRR_A : 0) |
			    VIP_CNTRL_0_SWAP_B(p->swap_b) |
			    (p->mirr_b ? VIP_CNTRL_0_MIRR_B : 0);
	priv->vip_cntrl_1 = VIP_CNTRL_1_SWAP_C(p->swap_c) |
			    (p->mirr_c ? VIP_CNTRL_1_MIRR_C : 0) |
			    VIP_CNTRL_1_SWAP_D(p->swap_d) |
			    (p->mirr_d ? VIP_CNTRL_1_MIRR_D : 0);
	priv->vip_cntrl_2 = VIP_CNTRL_2_SWAP_E(p->swap_e) |
			    (p->mirr_e ? VIP_CNTRL_2_MIRR_E : 0) |
			    VIP_CNTRL_2_SWAP_F(p->swap_f) |
			    (p->mirr_f ? VIP_CNTRL_2_MIRR_F : 0);

	priv->audio_params = p->audio_params;
}
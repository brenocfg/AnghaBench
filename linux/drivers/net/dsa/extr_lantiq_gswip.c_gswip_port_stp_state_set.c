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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct gswip_priv {int /*<<< orphan*/  dev; } ;
struct dsa_switch {struct gswip_priv* priv; } ;

/* Variables and functions */
#define  BR_STATE_BLOCKING 132 
#define  BR_STATE_DISABLED 131 
#define  BR_STATE_FORWARDING 130 
#define  BR_STATE_LEARNING 129 
#define  BR_STATE_LISTENING 128 
 int /*<<< orphan*/  GSWIP_PCE_PCTRL_0_PSTATE_FORWARDING ; 
 int /*<<< orphan*/  GSWIP_PCE_PCTRL_0_PSTATE_LEARNING ; 
 int /*<<< orphan*/  GSWIP_PCE_PCTRL_0_PSTATE_LISTEN ; 
 int /*<<< orphan*/  GSWIP_PCE_PCTRL_0_PSTATE_MASK ; 
 int /*<<< orphan*/  GSWIP_PCE_PCTRL_0p (int) ; 
 int /*<<< orphan*/  GSWIP_SDMA_PCTRL_EN ; 
 int /*<<< orphan*/  GSWIP_SDMA_PCTRLp (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gswip_switch_mask (struct gswip_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gswip_port_stp_state_set(struct dsa_switch *ds, int port, u8 state)
{
	struct gswip_priv *priv = ds->priv;
	u32 stp_state;

	switch (state) {
	case BR_STATE_DISABLED:
		gswip_switch_mask(priv, GSWIP_SDMA_PCTRL_EN, 0,
				  GSWIP_SDMA_PCTRLp(port));
		return;
	case BR_STATE_BLOCKING:
	case BR_STATE_LISTENING:
		stp_state = GSWIP_PCE_PCTRL_0_PSTATE_LISTEN;
		break;
	case BR_STATE_LEARNING:
		stp_state = GSWIP_PCE_PCTRL_0_PSTATE_LEARNING;
		break;
	case BR_STATE_FORWARDING:
		stp_state = GSWIP_PCE_PCTRL_0_PSTATE_FORWARDING;
		break;
	default:
		dev_err(priv->dev, "invalid STP state: %d\n", state);
		return;
	}

	gswip_switch_mask(priv, 0, GSWIP_SDMA_PCTRL_EN,
			  GSWIP_SDMA_PCTRLp(port));
	gswip_switch_mask(priv, GSWIP_PCE_PCTRL_0_PSTATE_MASK, stp_state,
			  GSWIP_PCE_PCTRL_0p(port));
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gswip_priv {int dummy; } ;
struct TYPE_3__ {int val_0; int val_1; int val_2; int val_3; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  GSWIP_PCE_GCTRL_0 ; 
 int /*<<< orphan*/  GSWIP_PCE_GCTRL_0_MC_VALID ; 
 int /*<<< orphan*/  GSWIP_PCE_TBL_ADDR ; 
 int /*<<< orphan*/  GSWIP_PCE_TBL_CTRL ; 
 int GSWIP_PCE_TBL_CTRL_ADDR_MASK ; 
 int /*<<< orphan*/  GSWIP_PCE_TBL_CTRL_BAS ; 
 int /*<<< orphan*/  GSWIP_PCE_TBL_CTRL_OPMOD_ADWR ; 
 int GSWIP_PCE_TBL_CTRL_OPMOD_MASK ; 
 int /*<<< orphan*/  GSWIP_PCE_TBL_MASK ; 
 int /*<<< orphan*/  GSWIP_PCE_TBL_VAL (int) ; 
 TYPE_1__* gswip_pce_microcode ; 
 int /*<<< orphan*/  gswip_switch_mask (struct gswip_priv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gswip_switch_r_timeout (struct gswip_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gswip_switch_w (struct gswip_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gswip_pce_load_microcode(struct gswip_priv *priv)
{
	int i;
	int err;

	gswip_switch_mask(priv, GSWIP_PCE_TBL_CTRL_ADDR_MASK |
				GSWIP_PCE_TBL_CTRL_OPMOD_MASK,
			  GSWIP_PCE_TBL_CTRL_OPMOD_ADWR, GSWIP_PCE_TBL_CTRL);
	gswip_switch_w(priv, 0, GSWIP_PCE_TBL_MASK);

	for (i = 0; i < ARRAY_SIZE(gswip_pce_microcode); i++) {
		gswip_switch_w(priv, i, GSWIP_PCE_TBL_ADDR);
		gswip_switch_w(priv, gswip_pce_microcode[i].val_0,
			       GSWIP_PCE_TBL_VAL(0));
		gswip_switch_w(priv, gswip_pce_microcode[i].val_1,
			       GSWIP_PCE_TBL_VAL(1));
		gswip_switch_w(priv, gswip_pce_microcode[i].val_2,
			       GSWIP_PCE_TBL_VAL(2));
		gswip_switch_w(priv, gswip_pce_microcode[i].val_3,
			       GSWIP_PCE_TBL_VAL(3));

		/* start the table access: */
		gswip_switch_mask(priv, 0, GSWIP_PCE_TBL_CTRL_BAS,
				  GSWIP_PCE_TBL_CTRL);
		err = gswip_switch_r_timeout(priv, GSWIP_PCE_TBL_CTRL,
					     GSWIP_PCE_TBL_CTRL_BAS);
		if (err)
			return err;
	}

	/* tell the switch that the microcode is loaded */
	gswip_switch_mask(priv, 0, GSWIP_PCE_GCTRL_0_MC_VALID,
			  GSWIP_PCE_GCTRL_0);

	return 0;
}
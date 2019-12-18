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
typedef  int u16 ;
struct gswip_priv {int dummy; } ;
struct gswip_pce_table_entry {int table; int type; int valid; int gmap; void* mask; void** val; void** key; int /*<<< orphan*/  index; scalar_t__ key_mode; } ;

/* Variables and functions */
 int ARRAY_SIZE (void**) ; 
 int /*<<< orphan*/  GSWIP_PCE_TBL_ADDR ; 
 int /*<<< orphan*/  GSWIP_PCE_TBL_CTRL ; 
 int GSWIP_PCE_TBL_CTRL_ADDR_MASK ; 
 int GSWIP_PCE_TBL_CTRL_BAS ; 
 int GSWIP_PCE_TBL_CTRL_GMAP_MASK ; 
 int GSWIP_PCE_TBL_CTRL_OPMOD_ADRD ; 
 int GSWIP_PCE_TBL_CTRL_OPMOD_KSRD ; 
 int GSWIP_PCE_TBL_CTRL_OPMOD_MASK ; 
 int GSWIP_PCE_TBL_CTRL_TYPE ; 
 int GSWIP_PCE_TBL_CTRL_VLD ; 
 int /*<<< orphan*/  GSWIP_PCE_TBL_KEY (int) ; 
 int /*<<< orphan*/  GSWIP_PCE_TBL_MASK ; 
 int /*<<< orphan*/  GSWIP_PCE_TBL_VAL (int) ; 
 int /*<<< orphan*/  gswip_switch_mask (struct gswip_priv*,int,int,int /*<<< orphan*/ ) ; 
 void* gswip_switch_r (struct gswip_priv*,int /*<<< orphan*/ ) ; 
 int gswip_switch_r_timeout (struct gswip_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gswip_switch_w (struct gswip_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gswip_pce_table_entry_read(struct gswip_priv *priv,
				      struct gswip_pce_table_entry *tbl)
{
	int i;
	int err;
	u16 crtl;
	u16 addr_mode = tbl->key_mode ? GSWIP_PCE_TBL_CTRL_OPMOD_KSRD :
					GSWIP_PCE_TBL_CTRL_OPMOD_ADRD;

	err = gswip_switch_r_timeout(priv, GSWIP_PCE_TBL_CTRL,
				     GSWIP_PCE_TBL_CTRL_BAS);
	if (err)
		return err;

	gswip_switch_w(priv, tbl->index, GSWIP_PCE_TBL_ADDR);
	gswip_switch_mask(priv, GSWIP_PCE_TBL_CTRL_ADDR_MASK |
				GSWIP_PCE_TBL_CTRL_OPMOD_MASK,
			  tbl->table | addr_mode | GSWIP_PCE_TBL_CTRL_BAS,
			  GSWIP_PCE_TBL_CTRL);

	err = gswip_switch_r_timeout(priv, GSWIP_PCE_TBL_CTRL,
				     GSWIP_PCE_TBL_CTRL_BAS);
	if (err)
		return err;

	for (i = 0; i < ARRAY_SIZE(tbl->key); i++)
		tbl->key[i] = gswip_switch_r(priv, GSWIP_PCE_TBL_KEY(i));

	for (i = 0; i < ARRAY_SIZE(tbl->val); i++)
		tbl->val[i] = gswip_switch_r(priv, GSWIP_PCE_TBL_VAL(i));

	tbl->mask = gswip_switch_r(priv, GSWIP_PCE_TBL_MASK);

	crtl = gswip_switch_r(priv, GSWIP_PCE_TBL_CTRL);

	tbl->type = !!(crtl & GSWIP_PCE_TBL_CTRL_TYPE);
	tbl->valid = !!(crtl & GSWIP_PCE_TBL_CTRL_VLD);
	tbl->gmap = (crtl & GSWIP_PCE_TBL_CTRL_GMAP_MASK) >> 7;

	return 0;
}
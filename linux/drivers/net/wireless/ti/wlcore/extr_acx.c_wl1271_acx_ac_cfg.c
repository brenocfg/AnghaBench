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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wl12xx_vif {int /*<<< orphan*/  role_id; } ;
struct wl1271 {int dummy; } ;
struct acx_ac_cfg {void* tx_op_limit; void* aifsn; void* cw_max; void* cw_min; void* ac; int /*<<< orphan*/  role_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_AC_CFG ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct acx_ac_cfg*) ; 
 struct acx_ac_cfg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct acx_ac_cfg*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,void*,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl1271_acx_ac_cfg(struct wl1271 *wl, struct wl12xx_vif *wlvif,
		      u8 ac, u8 cw_min, u16 cw_max, u8 aifsn, u16 txop)
{
	struct acx_ac_cfg *acx;
	int ret = 0;

	wl1271_debug(DEBUG_ACX, "acx ac cfg %d cw_ming %d cw_max %d "
		     "aifs %d txop %d", ac, cw_min, cw_max, aifsn, txop);

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);

	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	acx->role_id = wlvif->role_id;
	acx->ac = ac;
	acx->cw_min = cw_min;
	acx->cw_max = cpu_to_le16(cw_max);
	acx->aifsn = aifsn;
	acx->tx_op_limit = cpu_to_le16(txop);

	ret = wl1271_cmd_configure(wl, ACX_AC_CFG, acx, sizeof(*acx));
	if (ret < 0) {
		wl1271_warning("acx ac cfg failed: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}
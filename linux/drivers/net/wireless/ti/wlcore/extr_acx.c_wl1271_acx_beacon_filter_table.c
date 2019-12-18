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
struct wl12xx_vif {int /*<<< orphan*/  role_id; } ;
struct TYPE_3__ {int bcn_filt_ie_count; struct conf_bcn_filt_rule* bcn_filt_ie; } ;
struct TYPE_4__ {TYPE_1__ conn; } ;
struct wl1271 {TYPE_2__ conf; } ;
struct conf_bcn_filt_rule {scalar_t__ ie; scalar_t__ rule; scalar_t__ type; int /*<<< orphan*/  version; int /*<<< orphan*/  oui; } ;
struct acx_beacon_filter_ie_table {scalar_t__* table; scalar_t__ num_ie; int /*<<< orphan*/  role_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_BEACON_FILTER_TABLE ; 
 scalar_t__ CONF_BCN_IE_OUI_LEN ; 
 scalar_t__ CONF_BCN_IE_VER_LEN ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WLAN_EID_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  kfree (struct acx_beacon_filter_ie_table*) ; 
 struct acx_beacon_filter_ie_table* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct acx_beacon_filter_ie_table*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl1271_acx_beacon_filter_table(struct wl1271 *wl,
				   struct wl12xx_vif *wlvif)
{
	struct acx_beacon_filter_ie_table *ie_table;
	int i, idx = 0;
	int ret;
	bool vendor_spec = false;

	wl1271_debug(DEBUG_ACX, "acx beacon filter table");

	ie_table = kzalloc(sizeof(*ie_table), GFP_KERNEL);
	if (!ie_table) {
		ret = -ENOMEM;
		goto out;
	}

	/* configure default beacon pass-through rules */
	ie_table->role_id = wlvif->role_id;
	ie_table->num_ie = 0;
	for (i = 0; i < wl->conf.conn.bcn_filt_ie_count; i++) {
		struct conf_bcn_filt_rule *r = &(wl->conf.conn.bcn_filt_ie[i]);
		ie_table->table[idx++] = r->ie;
		ie_table->table[idx++] = r->rule;

		if (r->ie == WLAN_EID_VENDOR_SPECIFIC) {
			/* only one vendor specific ie allowed */
			if (vendor_spec)
				continue;

			/* for vendor specific rules configure the
			   additional fields */
			memcpy(&(ie_table->table[idx]), r->oui,
			       CONF_BCN_IE_OUI_LEN);
			idx += CONF_BCN_IE_OUI_LEN;
			ie_table->table[idx++] = r->type;
			memcpy(&(ie_table->table[idx]), r->version,
			       CONF_BCN_IE_VER_LEN);
			idx += CONF_BCN_IE_VER_LEN;
			vendor_spec = true;
		}

		ie_table->num_ie++;
	}

	ret = wl1271_cmd_configure(wl, ACX_BEACON_FILTER_TABLE,
				   ie_table, sizeof(*ie_table));
	if (ret < 0) {
		wl1271_warning("failed to set beacon filter table: %d", ret);
		goto out;
	}

out:
	kfree(ie_table);
	return ret;
}
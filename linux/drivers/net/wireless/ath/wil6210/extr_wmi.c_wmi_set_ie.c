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
typedef  size_t u8 ;
typedef  scalar_t__ u16 ;
struct wmi_set_appie_cmd {size_t mgmt_frm_type; int /*<<< orphan*/  ie_info; int /*<<< orphan*/  ie_len; } ;
struct wil6210_vif {int /*<<< orphan*/  mid; } ;
struct wil6210_priv {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const* const*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  WMI_FRAME_ASSOC_REQ 132 
#define  WMI_FRAME_ASSOC_RESP 131 
#define  WMI_FRAME_BEACON 130 
#define  WMI_FRAME_PROBE_REQ 129 
#define  WMI_FRAME_PROBE_RESP 128 
 int /*<<< orphan*/  WMI_SET_APPIE_CMDID ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct wmi_set_appie_cmd*) ; 
 struct wmi_set_appie_cmd* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,scalar_t__) ; 
 struct wil6210_priv* vif_to_wil (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,size_t,char const*,int) ; 
 int wmi_send (struct wil6210_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wmi_set_appie_cmd*,scalar_t__) ; 

int wmi_set_ie(struct wil6210_vif *vif, u8 type, u16 ie_len, const void *ie)
{
	struct wil6210_priv *wil = vif_to_wil(vif);
	static const char *const names[] = {
		[WMI_FRAME_BEACON]	= "BEACON",
		[WMI_FRAME_PROBE_REQ]	= "PROBE_REQ",
		[WMI_FRAME_PROBE_RESP]	= "WMI_FRAME_PROBE_RESP",
		[WMI_FRAME_ASSOC_REQ]	= "WMI_FRAME_ASSOC_REQ",
		[WMI_FRAME_ASSOC_RESP]	= "WMI_FRAME_ASSOC_RESP",
	};
	int rc;
	u16 len = sizeof(struct wmi_set_appie_cmd) + ie_len;
	struct wmi_set_appie_cmd *cmd;

	if (len < ie_len) {
		rc = -EINVAL;
		goto out;
	}

	cmd = kzalloc(len, GFP_KERNEL);
	if (!cmd) {
		rc = -ENOMEM;
		goto out;
	}
	if (!ie)
		ie_len = 0;

	cmd->mgmt_frm_type = type;
	/* BUG: FW API define ieLen as u8. Will fix FW */
	cmd->ie_len = cpu_to_le16(ie_len);
	memcpy(cmd->ie_info, ie, ie_len);
	rc = wmi_send(wil, WMI_SET_APPIE_CMDID, vif->mid, cmd, len);
	kfree(cmd);
out:
	if (rc) {
		const char *name = type < ARRAY_SIZE(names) ?
				   names[type] : "??";
		wil_err(wil, "set_ie(%d %s) failed : %d\n", type, name, rc);
	}

	return rc;
}
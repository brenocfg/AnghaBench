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
struct wmi_update_ft_ies_cmd {int /*<<< orphan*/  ie_info; int /*<<< orphan*/  ie_len; } ;
struct wil6210_vif {int /*<<< orphan*/  mid; } ;
struct wil6210_priv {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WMI_UPDATE_FT_IES_CMDID ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kfree (struct wmi_update_ft_ies_cmd*) ; 
 struct wmi_update_ft_ies_cmd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 struct wil6210_priv* vif_to_wil (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*,int) ; 
 int wmi_send (struct wil6210_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wmi_update_ft_ies_cmd*,int) ; 

int wmi_update_ft_ies(struct wil6210_vif *vif, u16 ie_len, const void *ie)
{
	struct wil6210_priv *wil = vif_to_wil(vif);
	u16 len;
	struct wmi_update_ft_ies_cmd *cmd;
	int rc;

	if (!ie)
		ie_len = 0;

	len = sizeof(struct wmi_update_ft_ies_cmd) + ie_len;
	if (len < ie_len) {
		wil_err(wil, "wraparound. ie len %d\n", ie_len);
		return -EINVAL;
	}

	cmd = kzalloc(len, GFP_KERNEL);
	if (!cmd) {
		rc = -ENOMEM;
		goto out;
	}

	cmd->ie_len = cpu_to_le16(ie_len);
	memcpy(cmd->ie_info, ie, ie_len);
	rc = wmi_send(wil, WMI_UPDATE_FT_IES_CMDID, vif->mid, cmd, len);
	kfree(cmd);

out:
	if (rc)
		wil_err(wil, "update ft ies failed : %d\n", rc);

	return rc;
}
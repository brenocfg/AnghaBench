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
typedef  int uint16_t ;
struct wireless_dev {scalar_t__ mesh_id_up_len; int /*<<< orphan*/  ssid; } ;
struct mrvl_meshie_val {int dummy; } ;
struct TYPE_4__ {int* oui; int /*<<< orphan*/  mesh_id; scalar_t__ mesh_id_len; int /*<<< orphan*/  mesh_capability; int /*<<< orphan*/  active_metric_id; int /*<<< orphan*/  active_protocol_id; int /*<<< orphan*/  version; int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; } ;
struct mrvl_meshie {TYPE_2__ val; scalar_t__ len; int /*<<< orphan*/  id; } ;
struct lbs_private {int /*<<< orphan*/  mesh_tlv; TYPE_1__* mesh_dev; } ;
struct cmd_ds_mesh_config {void* length; scalar_t__ data; void* channel; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_3__ {struct wireless_dev* ieee80211_ptr; } ;

/* Variables and functions */
#define  CMD_ACT_MESH_CONFIG_START 129 
#define  CMD_ACT_MESH_CONFIG_STOP 128 
 int /*<<< orphan*/  IEEE80211_MAX_SSID_LEN ; 
 int /*<<< orphan*/  MARVELL_MESH_CAPABILITY ; 
 int /*<<< orphan*/  MARVELL_MESH_IE_SUBTYPE ; 
 int /*<<< orphan*/  MARVELL_MESH_IE_TYPE ; 
 int /*<<< orphan*/  MARVELL_MESH_IE_VERSION ; 
 int /*<<< orphan*/  MARVELL_MESH_METRIC_ID ; 
 int /*<<< orphan*/  MARVELL_MESH_PROTO_ID_HWMP ; 
 int /*<<< orphan*/  WLAN_EID_VENDOR_SPECIFIC ; 
 int __lbs_mesh_config_send (struct lbs_private*,struct cmd_ds_mesh_config*,int,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  lbs_deb_cmd (char*,int,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_mesh_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lbs_mesh_config(struct lbs_private *priv, uint16_t action,
		uint16_t chan)
{
	struct wireless_dev *mesh_wdev;
	struct cmd_ds_mesh_config cmd;
	struct mrvl_meshie *ie;

	memset(&cmd, 0, sizeof(cmd));
	cmd.channel = cpu_to_le16(chan);
	ie = (struct mrvl_meshie *)cmd.data;

	switch (action) {
	case CMD_ACT_MESH_CONFIG_START:
		ie->id = WLAN_EID_VENDOR_SPECIFIC;
		ie->val.oui[0] = 0x00;
		ie->val.oui[1] = 0x50;
		ie->val.oui[2] = 0x43;
		ie->val.type = MARVELL_MESH_IE_TYPE;
		ie->val.subtype = MARVELL_MESH_IE_SUBTYPE;
		ie->val.version = MARVELL_MESH_IE_VERSION;
		ie->val.active_protocol_id = MARVELL_MESH_PROTO_ID_HWMP;
		ie->val.active_metric_id = MARVELL_MESH_METRIC_ID;
		ie->val.mesh_capability = MARVELL_MESH_CAPABILITY;

		if (priv->mesh_dev) {
			mesh_wdev = priv->mesh_dev->ieee80211_ptr;
			ie->val.mesh_id_len = mesh_wdev->mesh_id_up_len;
			memcpy(ie->val.mesh_id, mesh_wdev->ssid,
						mesh_wdev->mesh_id_up_len);
		}

		ie->len = sizeof(struct mrvl_meshie_val) -
			IEEE80211_MAX_SSID_LEN + ie->val.mesh_id_len;

		cmd.length = cpu_to_le16(sizeof(struct mrvl_meshie_val));
		break;
	case CMD_ACT_MESH_CONFIG_STOP:
		break;
	default:
		return -1;
	}
	lbs_deb_cmd("mesh config action %d type %x channel %d SSID %*pE\n",
		    action, priv->mesh_tlv, chan, ie->val.mesh_id_len,
		    ie->val.mesh_id);

	return __lbs_mesh_config_send(priv, &cmd, action, priv->mesh_tlv);
}